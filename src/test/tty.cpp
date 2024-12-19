#include <cstdio>
#include <termios.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include "tty.h"

//
// tty_device : mame device_t interface / status
//
DEFINE_DEVICE_TYPE(TTY, tty_device, "tty", "tty uart")

tty_device::tty_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock),
	m_rxrdy_handler(*this),
	m_txrdy_handler(*this),
	m_txempty_handler(*this)
{
	fprintf(stderr, "tty_device: constructor\n");
}

tty_device::tty_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: tty_device(mconfig, TTY, tag, owner, clock)
{
}

void tty_device::device_start(void)
{
	fprintf(stderr, "tty_device::device_start\n");
}

void tty_device::device_reset(void)
{
	fprintf(stderr, "tty_device::device_reset\n");
	tty::device_reset();
}

uint8_t tty_device::data_r(void) { return tty::read_data_register(); }
void tty_device::data_w(uint8_t data) { tty::write_data_register(data); }
uint8_t tty_device::status_r(void) { return tty::read_status_register(); }

uint8_t tty_device::read(offs_t offset)
{
	if (offset & 1) {
		// status register
		return status_r();
	} else {
		return data_r();
	}
}

void tty_device::write(offs_t offset, uint8_t data)
{
	if (offset & 1) {
		fprintf(stderr, "control_r: %02x\n", data);
	} else {
		data_w(data);
	}
}

void tty_device::write_tty(uint8_t ch)
{
	tty::put_write_data(ch);
}

int tty_device::txrdy_r()
{
	return (read_status_register() & TXRDY_Bit);
}


// class tty member functions

//
// get_100usec ... with clock_gettime, a new POSIC standard
//
tick_t tty::get_tick(void)
{
	struct timespec ts;
	tick_t current;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	// so far 10us tick
	current = (unsigned long int)ts.tv_sec * 100000L + ts.tv_nsec / 10000L;
	if (m_tick_start == 0)
		m_tick_start = current;
	current -= m_tick_start;
	//fprintf(stderr,"[%d]", current);
	return current;
}

//
// serial device upper layer
//
#define INPUT_TICK_PERIOD 50	// 500us

uint8_t tty::read_status_register(void)
{
	update_input_status();
	update_output_status();
	//fprintf(stderr, ".");
	return m_status_register;
}

// read-input

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

//
// file redirection
//

#define ASCIIART

/* Implementation for the input device */
void tty::reset_input_device(void)
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
	// tty object state initialize
	m_tick_start = 0;			// offset to absolute tick
	// input-read side
	m_previous_input_tick = 0;	// offset to input timer start
	m_read_data = 0xe5;
	m_read_data_ready = 0;
	m_status_register &= ~(RXRDY_Bit);
	// input redirect
	m_fp = NULL;
	m_file_flag = 1;
	m_filename = "ASCIIART.BAS";
	m_fd = STDIN_FILENO;
}

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

void tty::input_device_restore(void)
{
	changemode(0);
}

//
// Linux tty driver interface
//

void tty::changemode(int dir)
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

int tty::kbhit(void)
{
    struct timeval tv;
    fd_set rdfs;
	//tick_t current;

	//current = get_tick();
	//if (current - m_previous_kbhit_tick <= (100 * INPUT_TICK_PERIOD)) {
	//	return 0;
	//}
	//m_previous_kbhit_tick = current;

    tv.tv_sec = 0;
    tv.tv_usec = 10;

    FD_ZERO(&rdfs);
    FD_SET (m_fd, &rdfs);

    select(m_fd + 1, &rdfs, NULL, NULL, &tv);
	//if (m_fd != STDIN_FILENO)
	//	fprintf(stderr, "[s%d]", FD_ISSET(m_fd, &rdfs));
    return FD_ISSET(m_fd, &rdfs);
}

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
	switch (ch) {
	case 0x0f:
		reset_asciiart_input();
		break;
	}

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