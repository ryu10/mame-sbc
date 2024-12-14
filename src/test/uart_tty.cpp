// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai

// uart_device/tty_device : simple but generic UART / Linux tty device

#include <cstdio>
#include <termios.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include "uart_tty.h"

//
// tty_device : mame device_t interface / status
//
DEFINE_DEVICE_TYPE(TTY, tty_device, "tty", "tty uart")

tty_device::tty_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock),
    m_tick(set_timer(clock)), 
	m_rxrdy_handler(*this)
{
	fprintf(stderr, "tty_device: constructor, timer_period = %d\n", clock);
}

tty_device::tty_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: tty_device(mconfig, TTY, tag, owner, clock)
{
}

void tty_device::device_start(void)
{
	fprintf(stderr, "tty_device::device_start\n");
    m_timer_txd = timer_alloc(FUNC(tty_device::update_timer_txd), this);
    m_timer_rxd = timer_alloc(FUNC(tty_device::update_timer_rxd), this);
	reset_input_device();
}

void tty_device::device_reset(void)
{
	fprintf(stderr, "tty_device::device_reset\n");
	// reset rxd
	m_data_r = 0xe5;
	m_data_r_ready = 0;
	m_phase_rxd = 0;
	m_timer_rxd->reset(attotime::from_usec(m_tick));
	// reset txd
	m_data_w = 0xe3;
	m_data_w_empty = 1;
	m_data_w_ready = 0;
	m_timer_txd->reset();
}

//
// serial device upper layer
//

// status register preparation
//
// You can prepare a derived class to fit some 
// specific UART device.
//
uint8_t tty_device::update_status_r(void)
{
    // compose bits of status register
    // emuz80 bit assign
    // if (g_input_device_ready)
	//    c |= 1;
	// if (g_output_device_empty)
	//	  c |= 2;
    uint8_t c = 0;
    if (m_data_r_ready)
        c |= 1;
    if (m_data_w_ready == 0 && m_data_w_empty == 1) {
        c |= 2;
	}
	return c;
}

// data register read/write

uint8_t tty_device::data_r(void)
{
	if (m_data_r_ready)
		m_data_r_ready = 0;
	return m_data_r;
}

void tty_device::data_w(uint8_t data)
{
	m_data_w = data;
	m_data_w_ready = 0;
	if (m_data_w_empty) {
		putchar(m_data_w);
		start_timer_txd(0);
		m_data_w_empty = 0;
	} else {
		fprintf(stderr, "txd: overrun\n");
		m_data_w_overrun = 1;
	}
}

uint8_t tty_device::status_r(void)
{
    m_status = update_status_r();
    return m_status;
}

// timer

// timer period
time_t tty_device::set_timer(time_t baudrate)
{
	time_t tick = 50;	// about 9800bps ... 50us per pulse-width
	if (baudrate > 0)
		tick  = 500000 / baudrate;
	// 1/2 cycle (1 pulse-width)
	fprintf(stderr, "tick: %ld usec\n", tick);
	return tick;
}

void tty_device::update_timer_rxd(s32 count) {
	uint8_t ch;
    switch(m_phase_rxd) {
    case 0: // none, polling timer
        if (m_data_r_ready == 0 && kbhit()) {
            // read and fill, shift to phase 1
            ch = getchar();
			// never occur overrun
			m_data_r = ch;
			m_data_r_ready = 1;

			m_phase_rxd++;
			m_timer_rxd->adjust(attotime::from_usec(20 * m_tick));
        } else {
			// keep to poll it
			m_timer_rxd->adjust(attotime::from_usec(m_tick));
		}
        break;
	case 1: // character timer expires, return to mode 0
		m_phase_rxd = 0;
		m_timer_rxd->adjust(attotime::from_usec(m_tick));
		break;
	default:
		fprintf(stderr, "update_timer_rxd: unexpected state\n");
		m_phase_rxd = 0;
		m_timer_rxd->adjust(attotime::from_usec(m_tick));
		break;
    } 
}

void tty_device::start_timer_txd(s32 count) {
	m_phase_txd = 1;
	m_timer_txd->adjust(attotime::from_usec(20 * m_tick));
}

void tty_device::update_timer_txd(int count) {
	if (m_phase_txd == 1) {
		// expires txd timer
		m_phase_txd = 0;
		// flush output char if data_w has one
		if (m_data_w_ready) {
			putchar(m_data_w);
			m_data_w_ready = 0;
			m_data_w_empty = 0;
		} else {
			// sending data is gone, now it it empty
			m_data_w_empty = 1;
		}
	} else {
		fprintf(stderr, "update_timer_txd: unexpected state\n");
	}
}

// class tty member functions

// read-input
#if 0
void tty::update_input_status(void)
{
	tick_t current = get_tick();
	uint8_t c;
	// input-read process
	//fprintf(stderr, "[%d,%02x]", m_read_data_ready, m_status_register);
	if (current - m_previous_input_tick <= INPUT_TICK_PERIOD) {
		return;
	}
	// timer expired
	if (m_read_data_ready) {
		//fprintf(stderr,"1");
		return;
	}
	// input data empty
	if (!kbhit()) {
		//fprintf(stderr,"2");
		return;
	}
	// read_data empty && input data ready
	c= get_key_input();	// should not been blocked
	m_previous_input_tick = current;
	// upper layer (set read_data)
	m_read_data = c;
	m_read_data_ready = 1;
	m_status_register |= RXRDY_Bit;	// RXRDY
	//fprintf(stderr, "(%d,%02x,%02x)", m_read_data_ready, m_status_register, c);
	return;
}

uint8_t tty::read_data_register(void)
{
	tick_t current;
	uint8_t c;

	if (m_read_data_ready) {
		c = m_read_data;
		m_read_data_ready = 0;
		m_status_register &= ~(RXRDY_Bit);	// RXRDY
		//fprintf(stderr, "{a%02x}", c);
		return c;
	}
	// input data empty
	current = get_tick();
	if (current - m_previous_input_tick <= INPUT_TICK_PERIOD) {
		// status unchanged, bogus data returns
		c = m_read_data;
		//fprintf(stderr, "{b%02x}", c);
		return c;
	}
	if (!kbhit()) {
		// status unchanged, bogus data returns
		c = m_read_data;
		//fprintf(stderr, "{c%02x}", c);
		return c;
	}
	// input data available, extract it and set
	c= get_key_input();			// should not been blocked
	m_previous_input_tick = current;
	// upper_layer (set read_data)
	m_read_data = c;
	m_read_data_ready = 1;
	m_status_register |= RXRDY_Bit;	// RXRDY set
	// again, clear read data 
	c = m_read_data;
	m_read_data_ready = 0;
	m_status_register &= ~RXRDY_Bit;// RXRDY clear
	//fprintf(stderr, "{d%02x}", c);
	return c;
}

// write-output

void tty::update_output_status(void)
{
	tick_t current = get_tick();

	// write-output process
	if (current - m_previous_output_tick <= INPUT_TICK_PERIOD) {
		// output in the lower layer ongoing
		m_output_empty = 0;
		m_status_register &= ~(TXEMPTY_Bit);
		return;
	}
	// lower layer empty
	if (m_output_data_pending) {
		// flush it
		put_write_data(m_output_data);
		current = get_tick();
		m_previous_output_tick = current;
		// upper status
		m_output_data_pending = 0;
		m_status_register |= TXRDY_Bit;
		// lower status
		m_output_empty = 0;
		m_status_register &= ~(TXEMPTY_Bit);
		return;
	}
	// no pending write data
	// output timer exhausted
	m_output_empty = 1;
	m_status_register |= (TXEMPTY_Bit);
	//fprintf(stderr, "<%d,%02x>", m_output_data_pending, m_status_register);
	return;
}

void tty::write_data_register(uint8_t data)
{
	tick_t current;
	// Anyway, lower layer write executing,
	// We do not assume no pending data exist.
	//fprintf(stderr, "-%02x-", data);
	m_output_data = data;
	put_write_data(m_output_data);
	current = get_tick();
	m_previous_output_tick = current;
	// upper status
	m_output_data_pending = 0;
	m_status_register |= TXRDY_Bit;
	// lower status
	m_output_empty = 0;
	m_status_register &= ~(TXEMPTY_Bit);
}

// device_reset
void tty::device_reset(void)
{
	reset_input_device();
	reset_output_device();
}

#endif
//
// file redirection
//

//#define ASCIIART

/* Implementation for the input device */
void tty_device::reset_input_device(void)
{
	changemode(1);
	// I have tried (and failed) to flush pending input by doing
	//  while (kbhit())
	//     osd_get_char();
	// but it did not work. (One character remains in input buffer, 
	// by typing second char, it returns 1st char)
	// I don't know why it did not work, but I recognize omitting this code
	// make it works.
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	fprintf(stderr, "reset_input_device\n");

	// input redirect
	//m_fp = NULL;
	//m_file_flag = 1;
	//m_filename = "ASCIIART.BAS";
	//m_fd = STDIN_FILENO;
}

#if 0
void tty::reset_output_device(void)
{
	// write-output side
	m_previous_output_tick = 0;	// offset to output timer start
	m_output_data = 0x48;
	m_output_empty = 1;
	m_output_data_pending = 0;
	m_status_register |= (TXRDY_Bit|TXEMPTY_Bit);
}

// lower layer (linux/Unix dependent)

void tty::reset_asciiart_input(void)
{
#ifdef ASCIIART
	fprintf(stderr, "open asciiart\n");
    // startup key-in from ASCIIART.BAS
    if ((m_fp = fopen(m_filename, "r")) == NULL) {
        fprintf(stderr, "%s cannot open\n", m_filename);
    }
	if (m_fp) {
		m_fd = fileno(m_fp);
		fprintf(stderr, "m_fd: %d\n", m_fd);
	}
#endif
}
#endif

void tty_device::input_device_restore(void)
{
	changemode(0);
}

//
// Linux tty driver interface
//

void tty_device::changemode(int dir)
{
  static struct termios oldt, newt;

  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_iflag &= ~( IGNCR | ICRNL );
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int tty_device::kbhit(void)
{
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 10;

    FD_ZERO(&rdfs);
    FD_SET(m_fd, &rdfs);

    select(m_fd + 1, &rdfs, NULL, NULL, &tv);
	//if (m_fd != STDIN_FILENO)
	//	fprintf(stderr, "[s%d]", FD_ISSET(m_fd, &rdfs));
    return FD_ISSET(m_fd, &rdfs);
}

#if 0
int tty::get_key_input(void)
{
    int ch;

#ifdef ASCIIART
    // redirected input
    if (m_file_flag && m_fp) {
        ch = fgetc(m_fp);
        if (ch != EOF) {
			fprintf(stderr, "%c", ch);
            return ch;
        }
        fclose(m_fp);
        m_fp = NULL;
        m_file_flag = 0;
		m_fd = STDIN_FILENO;
        // falling down
    }
#endif

  	ch = getchar();
#ifdef ASCIIART
	switch (ch) {
	case 0x0f:
		reset_asciiart_input();
		break;
	}
#endif

    if (ch == 0x7f)
        ch = 0x08;
    return ch;
}

void tty::put_write_data(uint8_t data)
{
	static tick_t start = 0;
	tick_t current;
	if (data == 0x0b) {
			// Ctrl-K
		start = get_tick();
		fprintf(stderr, "start\n");
	} else if (data == 0x0c) {
		current = get_tick() - start;
		fprintf(stderr, "time: %dmsec\n", current/100);
	} else {
		printf("%c", data);
	}
}

#endif
