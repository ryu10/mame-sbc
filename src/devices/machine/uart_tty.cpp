// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai

// uart_device : simple but generic UART / Linux tty device

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include "uart_tty.h"

//
// uart_device : mame device_t interface / status
//
DEFINE_DEVICE_TYPE(UART, uart_device, "uart", "uart on tty driver")

uart_device::uart_device(const machine_config &mconfig, 
						device_type type, 
						const char *tag, 
						device_t *owner, 
						uint32_t baudrate)
	: device_t(mconfig, type, tag, owner, baudrate),
	m_rxrdy_handler(*this)
{
	fprintf(stderr, "uart_device: constructor, baudrate = %d\n", m_clock);
}

uart_device::uart_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: uart_device(mconfig, UART, tag, owner, clock)
{
}

void uart_device::device_start(void)
{
	fprintf(stderr, "uart_device::device_start, tick = %ld\n", get_tick());
    m_timer_txd = timer_alloc(FUNC(uart_device::update_timer_txd), this);
    m_timer_rxd = timer_alloc(FUNC(uart_device::update_timer_rxd), this);
	reset_input_device();
}

void uart_device::device_reset(void)
{
	fprintf(stderr, "uart_device::device_reset\n");
	// reset rxd
	m_data_r = 0xe5;
	m_data_r_ready = 0;
	m_phase_rxd = 0;
	m_timer_rxd->reset(attotime::from_usec(get_tick()));
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
uint8_t uart_device::update_status_r(void)
{
    // compose bits of status register
    // emuz80 bit assign
    // if (g_input_device_ready)
	//    c |= 1;
	// if (g_output_device_empty)
	//	  c |= 2;
    uint8_t c = 0;
    if (m_data_r_ready) {
        c |= 1;
	}
    if (m_data_w_ready == 0 && m_data_w_empty == 1) {
        c |= 2;
	}
	return c;
}

// data register read/write

uint8_t uart_device::data_r(void)
{
	if (m_data_r_ready) {
		m_data_r_ready = 0;
		m_rxrdy_handler(0);
	}
	return m_data_r;
}

void uart_device::data_w(uint8_t data)
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

uint8_t uart_device::status_r(void)
{
    m_status = update_status_r();
    return m_status;
}

// timer period
// baudrate to timer cycle period convertion
time_t uart_device::get_tick(void)
{
	// tick represent period-length corresponding to 1/2 of baudrate
	time_t tick = 50;	// about 9800bps ... 50us per pulse-width
	if (m_clock > 0)
		tick  = 500000 / m_clock;
	return tick;
}

void uart_device::set_baudrate(time_t baudrate) { m_clock = baudrate; }

void uart_device::update_timer_rxd(s32 count) {
	uint8_t ch;
    switch(m_phase_rxd) {
    case 0: // none, polling timer
        if (m_data_r_ready == 0 && kbhit()) {
            // read and fill, shift to phase 1
            ch = getch();
			// never occur overrun
			m_data_r = ch;
			m_data_r_ready = 1;
			m_rxrdy_handler(1);		// asser RxRDY
			m_phase_rxd++;
			m_timer_rxd->adjust(attotime::from_usec(20 * get_tick()));
        } else {
			// keep to poll it
			m_timer_rxd->adjust(attotime::from_usec(get_tick()));
		}
        break;
	case 1: // character timer expires, return to mode 0
		m_phase_rxd = 0;
		m_timer_rxd->adjust(attotime::from_usec(get_tick()));
		break;
	default:
		fprintf(stderr, "update_timer_rxd: unexpected state\n");
		m_phase_rxd = 0;
		m_timer_rxd->adjust(attotime::from_usec(get_tick()));
		break;
    } 
}

void uart_device::start_timer_txd(s32 count) {
	m_phase_txd = 1;
	m_timer_txd->adjust(attotime::from_usec(20 * get_tick()));
}

void uart_device::update_timer_txd(int count) {
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

//
// file redirection
//

/* Implementation for the input device */
void uart_device::reset_input_device(void)
{
	changemode(1);
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	fprintf(stderr, "reset_input_device\n");

#ifdef REDIRECT
	// input redirect
	m_fp = NULL;
	m_file_flag = 1;
	m_filename = "ASCIIART.BAS";
	m_fd = STDIN_FILENO;
#endif
}

void uart_device::reset_asciiart_input(void)
{
#ifdef REDIRECT
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

void uart_device::input_device_restore(void)
{
	changemode(0);
}

//
// Linux tty driver interface
//

void uart_device::changemode(int dir)
{
  	static struct termios oldt, newt;

  	if ( dir == 1 ) {
    	tcgetattr( STDIN_FILENO, &oldt);
    	newt = oldt;
    	newt.c_iflag &= ~( IGNCR | ICRNL );
    	newt.c_lflag &= ~( ICANON | ECHO );
    	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  	} else {
    	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	}
}

int uart_device::kbhit(void)
{
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 10;

    FD_ZERO(&rdfs);
    FD_SET(m_fd, &rdfs);

    select(m_fd + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(m_fd, &rdfs);
}

int uart_device::getch(void)
{
    int ch;

#ifdef REDIRECT
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
#ifdef REDIRECT
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
