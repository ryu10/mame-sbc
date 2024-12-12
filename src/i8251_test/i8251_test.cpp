// license:BSD-3-Clause
// copyright-holders:Jonathan Gevaryahu, Robbbert, Miodrag Milanovic
/******************************************************************************

  An emulation for i8251_test, by @vintagechips (Den'noh-Densetsu),
  URL: https://vintagechips.wordpress.com/2018/06/24/i8251_test-cpu%E3%83%AB%E3%83%BC%E3%82%BA%E3%82%AD%E3%83%83%E3%83%88/

  It consists of 8080+8224+8228, ROM, RAM, and 8251.  It is a UART with 
  interrupt driven.
******************************************************************************/

#include "emu.h"	// for offs_t declaration
#include "cpu/z80/z80.h"
#include "machine/i8251.h"
#include "i8251_test.h"
#include "interface.h"
//#include "tty.h"
#include "blink.h"

#include <cstdio>
#include <cstdlib>

class i8251_test_state;
static class i8251_test_state *g_i8251_test;

class i8251_test_state : public driver_device
{
public:
	i8251_test_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_main_ram(*this, "main_ram"),
		m_uart(*this, "uart"),
		m_blink(*this, "blink")
	{
		//m_tty = new tty();
		g_i8251_test = this;
		fprintf(stderr, "i8251_test_state: constructor\n");
	}

	uint8_t uart_creg_r();
	uint8_t uart_dreg_r();
	//uint8_t watcher_memory_r(offs_t offset);
	void uart_creg_w(uint8_t data);
	void uart_dreg_w(uint8_t data);
	//void watcher_memory_w(offs_t offset, uint8_t data);
	//void display_w(offs_t offset, uint8_t data);
	void update_int_line(void);

	void z80_mem(address_map &map) ATTR_COLD;
	void io_map(address_map &map) ATTR_COLD;
	void i8251_test(machine_config &config);

	void int_line(int state);
	//void update_tty_state(uint8_t state) { m_tty->device_update(state); };
	void do_blink(int state);

private:
	required_device<z80_device> m_maincpu;
	required_shared_ptr<uint8_t> m_main_ram;
	required_device<i8251_device> m_uart;
	//std::string terminate_string;
	//tty *m_tty;
	required_device<blink_device> m_blink;
	//int m_tty_state;
	// int line state
	int m_prev_int_line = -1;
	uint8_t FF00_value = 0xff;
	// watcher memory
	//uint8_t m_watcher[16];

	virtual void machine_reset() override ATTR_COLD;

};

#if 0
static void irq_callback(offs_t offset, uint8_t value)
{
	static uint8_t prev_input = 0xff;
	if (offset == IRQ_INPUT_DEVICE) {
		if (prev_input != value) {
		    g_i8251_test->int_line(value ? ASSERT_LINE : CLEAR_LINE);
			prev_input = value;
		}
	}
}
#endif

/******************************************************************************
 Machine Start/Reset
******************************************************************************/

void i8251_test_state::machine_reset()
{
	//terminate_string = "";

	// program is self-modifying, so need to refresh it on each run
	memcpy(m_main_ram, i8251_test_binary, sizeof i8251_test_binary);
	// serial reset
	//m_tty->set_irq_cb(irq_callback);
	fprintf(stderr, "machine_reset\n");
}


/******************************************************************************
 I/O Handlers
******************************************************************************/

uint8_t i8251_test_state::uart_creg_r()
{
	return m_uart->status_r();
}

void i8251_test_state::uart_creg_w(uint8_t data)
{
	//fprintf(stderr, "uart_creg_w: %02x\n", data);
	m_uart->control_w(data);
}

uint8_t i8251_test_state::uart_dreg_r()
{
	uint8_t ch;
	ch = m_uart->data_r();
	return ch;
}

void i8251_test_state::uart_dreg_w(uint8_t data)
{
	m_uart->data_w(data);
}

void i8251_test_state::do_blink(int state)
{
	printf("%d", state);
}


#if 0
// watcher ... キー入力監視ワークエリアのアドレスを探し出して叩く。
uint8_t i8251_test_state::watcher_memory_r(offs_t offset)
{
	uint8_t b = m_watcher[offset];
	//sleep(1);
	//fprintf(stderr, "R[%04x:%02x]\n", offset, b);
	update_int_line();
	return b;
}

void i8251_test_state::watcher_memory_w(offs_t offset, uint8_t data)
{
	//fprintf(stderr, "W[%04x:%02x]\n", offset, data);
	m_watcher[offset] = data;
}

void i8251_test_state::update_int_line(void)
{
	uint8_t status_register;
	status_register = m_tty->read_status_register();
	int status_flag = (status_register & RXRDY_Bit) != 0;
	int line_flag = (m_prev_int_line == ASSERT_LINE);
	int toggle_line = line_flag ? CLEAR_LINE : ASSERT_LINE;
	if (status_flag != line_flag) {
		int_line(toggle_line);
		m_prev_int_line = toggle_line;
		//fprintf(stderr, "(I%d)", toggle_line);
	}
}
#endif

/******************************************************************************
 Address Maps
******************************************************************************/

void i8251_test_state::z80_mem(address_map &map)
{
	map(0x0000, 0xffff).ram().share("main_ram");
	//fprintf(stderr, "WATCH_ADDR: %04X\n", WATCH_ADDR);
	//map(WATCH_ADDR,WATCH_ADDR).rw(FUNC(i8251_test_state::watcher_memory_r),FUNC(i8251_test_state::watcher_memory_w));
}

void i8251_test_state::io_map(address_map &map)
{
	map.unmap_value_high();
	map.global_mask(0xff);
	map(0x00, 0x00).rw(FUNC(i8251_test_state::uart_dreg_r),FUNC(i8251_test_state::uart_dreg_w));
	map(0x01, 0x01).rw(FUNC(i8251_test_state::uart_creg_r),FUNC(i8251_test_state::uart_creg_w));

}

/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( i8251_test )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void i8251_test_state::i8251_test(machine_config &config)
{
	/* basic machine hardware */
	//Z80(config, m_maincpu, XTAL(3'579'545));
	Z80(config, m_maincpu, XTAL(20'000'000));
	I8251(config, m_uart, 100);
	BLINK(config, m_blink, (u32)100);
	m_blink->output_cb().set(FUNC(i8251_test_state::do_blink));
	m_maincpu->set_addrmap(AS_PROGRAM, &i8251_test_state::z80_mem);
	m_maincpu->set_addrmap(AS_IO, &i8251_test_state::io_map);
	// register a hook to z80 instruction execution loop
	//m_maincpu->execute_run_cb().set(*this, FUNC(i8251_test_state::update_tty_state));
}

/*
 * int handler
 */

void i8251_test_state::int_line(int state)
{
	m_maincpu->set_input_line(INPUT_LINE_IRQ0, state);
}
/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START(i8251_test)
	ROM_REGION(0x0, "maincpu", 0)
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT      COMPAT  MACHINE   INPUT   STATE         INIT        COMPANY                         FULLNAME                            FLAGS */
COMP( 2024, i8251_test,   0,          0,      i8251_test,   i8251_test, i8251_test_state, empty_init, "VintageChips", "i8251_test (Z80 with PIC18F47Q53)", MACHINE_NO_SOUND_HW )
