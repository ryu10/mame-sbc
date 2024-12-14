// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai

// uart_device/tty_device : simple but generic UART / Linux tty device

#ifndef HEADER_TTY
#define HEADER_TTY

#include "emu.h"
#include "schedule.h"
#include "osdcomm.h"
#include "devcb.h"

#include <time.h>
#include <unistd.h>

// tick timer counter type (internal only)
typedef int32_t tick_t;

// Data regisger/Control register
#define TTY_DR 0
#define TTY_CR 1
#define TTY_SR 1

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

// device type definition
DECLARE_DEVICE_TYPE(TTY, tty_device)

class tty_device : public device_t {
public:
	// configuration helpers
    // usually for INT line
    // usually for INT line
	auto rxrdy_handler() { return m_rxrdy_handler.bind(); }

	tty_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

    // CPU interface
	uint8_t status_r();
	uint8_t data_r();
	void data_w(uint8_t data);

    //uint8_t read_status_register(void);
    //uint8_t read_data_register(void);
    //void write_data_register(uint8_t value);
    // set a callback function
    // void set_irq_cb(void (*fptr)(offs_t offset, uint8_t value)) { tty_irq_cb = fptr; };

protected:
	tty_device(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			uint32_t clock);

	// device_t implementation
	virtual void device_start() override ATTR_COLD;
	virtual void device_reset() override ATTR_COLD;

    // register tweaking
    virtual uint8_t update_status_r(void);

private:
    // input_device
    //void reset_input_device(void);
    //void update_input_status(void);
    // output_device
    //void reset_output_device(void);
    //void update_output_status(void);

    // timer state
    // timed update callback
	TIMER_CALLBACK_MEMBER(update_timer_txd);
	TIMER_CALLBACK_MEMBER(update_timer_rxd);

	// tick ... 1/2

    void start_timer_txd(int clock);

    // callbacks
	//devcb_write_line m_output_cb;
	// timer
	emu_timer *m_timer_txd;
    emu_timer *m_timer_rxd;
    // speed (bps)
	time_t set_timer(time_t baudrate);
    time_t m_tick;      // unit: usec, 1/2 pulse-width, or 1/4 cycle-period-width
	// internal state
	int m_phase_rxd;    // 0: none, 1: after-receive dead mode, 2: over
	int m_phase_txd;

    // upper interface
    devcb_write_line m_rxrdy_handler;	// RxRDY line (for CPU INT0)

    // upper layer registers
    uint8_t m_status = (TXRDY_Bit|TXEMPTY_Bit);
    uint8_t m_data_r;
    uint8_t m_data_w;

    // internal state
	int m_data_r_ready = 0;
    int m_data_w_ready = 0;
    int m_data_w_empty = 0;
	// error flag
	int m_data_r_overrun = 1;
	int m_data_w_overrun = 0;

	// lower layer (terminal device)
	int kbhit(void);
	// input redirect
	//FILE *m_fp = NULL;
	//int m_file_flag = 1;
    int m_fd = STDIN_FILENO;
	void changemode(int dir);
	//const char *m_filename = "ASCIIART.BAS";

    // file input redirection
    //void reset_asciiart_input(void);
	void reset_input_device(void);
    void input_device_restore(void);
};

#if 0
// device type definition
DECLARE_DEVICE_TYPE(UART, uart_device)

class uart_device : public device_t
{
public:
	// configuration helpers
    // usually for INT line
	auto rxrdy_handler() { return m_rxrdy_handler.bind(); }
	auto txrdy_handler() { return m_txrdy_handler.bind(); }
	auto txempty_handler() { return m_txempty_handler.bind(); }

	// construction/destruction
	uart_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

    // CPU interface
	uint8_t status_r();
	uint8_t data_r();
	void data_w(uint8_t data);

	virtual uint8_t read(offs_t offset);
	virtual void write(offs_t offset, uint8_t data);

    // lower layer interface
    void update_tty_db(u8 value);   // callback (to be called by tty_device)

protected:
	enum
	{
		TTY_STATUS_FRAMING_ERROR = 0x20,
		TTY_STATUS_OVERRUN_ERROR = 0x10,
		TTY_STATUS_PARITY_ERROR = 0x08,
		TTY_STATUS_TX_EMPTY = 0x04,
		TTY_STATUS_RX_READY = 0x02,
		TTY_STATUS_TX_READY = 0x01
	};

	uart_device(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			uint32_t clock);

	// device_t implementation
	virtual void device_start() override ATTR_COLD;
	virtual void device_reset() override ATTR_COLD;

	//void command_w(uint8_t data);
	//void mode_w(uint8_t data);

	//void receive_character(uint8_t ch);

	//void update_rx_ready();
	//void update_tx_ready();
	//void update_tx_empty();
	//void transmit_clock();
	//void receive_clock();
	//bool is_tx_enabled() const;
	//void check_for_tx_start();
	//void start_tx();

private:

	devcb_write_line m_rxrdy_handler;
	devcb_write_line m_txrdy_handler;
	devcb_write_line m_txempty_handler;

	/* flags controlling how tty_control_w operates */
	uint8_t m_flags;
	/* status of i8251 */
	uint8_t m_status;
	uint8_t m_data_r;
    uint8_t m_data_w;
};

#endif

#endif /* HEADER_TTY */
