#ifndef HEADER__TTY
#define HEADER__TTY

#include "emu.h"
#include <time.h>
#include <unistd.h>

/**************************************************************
  8251 emulation
 **************************************************************/

// Data regisger/Control register
#define I8251_DR 0
#define I8251_CR 1
#define I8251_SR 1

// Status Register
#define DSR_Bit (1<<7)
#define SYNDET_Bit  (1<<6)
#define FE_Bit  (1<<5)
#define OE_Bit  (1<<4)
#define PE_Bit  (1<<3)
#define TXEMPTY_Bit (1<<2)
#define RXRDY_Bit (1<<1)
#define TXRDY_Bit (1<<0)

/* Time between characters sent to output device (seconds) */
// changed as milliseconds about 10000bps serial speed
#define OUTPUT_DEVICE_PERIOD 5

// tick timer counter type (internal only)
typedef int32_t tick_t;

class tty {
public:
    void device_reset(void);
    //void device_update(uint8_t state);
    uint8_t read_status_register(void);
    uint8_t read_data_register(void);
    void write_data_register(uint8_t value);
    // set a callback function
    //void set_irq_cb(void (*fptr)(offs_t offset, uint8_t value)) { tty_irq_cb = fptr; };

private:
    // input_device
    void reset_input_device(void);
    void update_input_status(void);
    // output_device
    void reset_output_device(void);
    void update_output_status(void);

private:
	// tty object state initialize
	tick_t m_tick_start = 0;			// offset to absolute tick
	// input-read side
	tick_t m_previous_input_tick = 0;	// offset to input timer start
	uint8_t m_read_data = 0xe5;
	int m_read_data_ready = 0;
	// write-output side
	tick_t m_previous_output_tick = 0;	// offset to output timer start
	uint8_t m_output_data = 0x48;
	int m_output_empty = 1;
	int m_output_data_pending = 0;
    // status_register
    uint8_t m_status_register = (TXRDY_Bit|TXEMPTY_Bit);
	// input redirect
	FILE *m_fp = NULL;
	int m_file_flag = 1;
    int m_fd = STDIN_FILENO;
	const char *m_filename = "ASCIIART.BAS";
    // kbhit interval timer
    int m_previous_kbhit_tick = 0;

    int     quit = 0;
    int     nmi = 0;

    // callback vector
    // offset: 0: input irq assert/clear
    //         1: output irq assert/clear
    // value:  0: clear
    //         1: assert
    //void (*tty_irq_cb)(offs_t offset, uint8_t value) = nullptr;
#define IRQ_INPUT_DEVICE 0
#define IRQ_OUTPUT_DEVICE 1

    // file input redirection
    void reset_asciiart_input(void);
    void input_device_restore(void);

    // linux tty driver
    void changemode(int dir);
    int kbhit(void);
    int get_key_input(void);
    void put_write_data(uint8_t c);
    // get_100usec
    tick_t get_tick(void);
};


#endif /* HEADER__TTY */

