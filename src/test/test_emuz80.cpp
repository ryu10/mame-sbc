// license:BSD-3-Clause
// copyright-holders:Norihiro Kumagai
/******************************************************************************

  SBC test board system

******************************************************************************/

#include "emu.h"	// for offs_t declaration
#include "cpu/z80/z80.h"
#include "test_emuz80.h"
#include "machine/uart_tty.h"

#include <cstdio>
#include <cstdlib>

//
// test_state : test application framework
//

// Z80 and generic UART version

class test_state : public driver_device
{
public:
	test_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_main_ram(*this, "main_ram"),
		m_uart(*this, "uart")
	{
		fprintf(stderr, "test_state: constructor\n");
	}

	uint8_t uart_creg_r();
	uint8_t uart_dreg_r();
	void uart_creg_w(uint8_t data);
	void uart_dreg_w(uint8_t data);

	void z80_mem(address_map &map) ATTR_COLD;
	void io_map(address_map &map) ATTR_COLD;
	void test(machine_config &config);

	void sbc_int_w(int state);	// drive Z80 int line

private:
	required_device<z80_device> m_maincpu;
	required_shared_ptr<uint8_t> m_main_ram;
	required_device<uart_device> m_uart;

	virtual void machine_reset() override ATTR_COLD;

};

/******************************************************************************
 Machine Start/Reset
******************************************************************************/

void test_state::machine_reset()
{
	// program is self-modifying, so need to refresh it on each run
	memcpy(m_main_ram, test_binary, sizeof test_binary);
	fprintf(stderr, "machine_reset\n");
}


/******************************************************************************
 I/O Handlers
******************************************************************************/

uint8_t test_state::uart_dreg_r() { return m_uart->data_r(); }
void    test_state::uart_dreg_w(uint8_t data) { m_uart->data_w(data); }
uint8_t test_state::uart_creg_r() {	return m_uart->status_r(); }
void    test_state::uart_creg_w(uint8_t data) {
	fprintf(stderr, "uart_creg_w: %02x\n", data);
}

/******************************************************************************
 Address Maps
******************************************************************************/

void test_state::z80_mem(address_map &map)
{
	map(0x0000, 0xffff).ram().share("main_ram");
	map(0xe000, 0xe000).rw(FUNC(test_state::uart_dreg_r),FUNC(test_state::uart_dreg_w));
	map(0xe001, 0xe001).rw(FUNC(test_state::uart_creg_r),FUNC(test_state::uart_creg_w));
}

void test_state::io_map(address_map &map)
{
	map.unmap_value_high();
	map.global_mask(0xff);
	map(0x00, 0x00).rw(FUNC(test_state::uart_dreg_r),FUNC(test_state::uart_dreg_w));
	map(0x01, 0x01).rw(FUNC(test_state::uart_creg_r),FUNC(test_state::uart_creg_w));

}

/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( test )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void test_state::test(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(20'000'000));
	UART(config, m_uart, 9600);
	m_maincpu->set_addrmap(AS_PROGRAM, &test_state::z80_mem);
	m_maincpu->set_addrmap(AS_IO, &test_state::io_map);
}

/*
 * int handler
 */

void test_state::sbc_int_w(int state)
{
	m_maincpu->set_input_line(INPUT_LINE_IRQ0, state);
}

/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START(test)
	ROM_REGION(0x0, "maincpu", 0)
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT      COMPAT  MACHINE   INPUT   STATE         INIT        COMPANY                         FULLNAME                            FLAGS */
COMP( 2024, test,   0,          0,      test,   test, test_state, empty_init, "VintageChips", "test (Z80 with PIC18F47Q53)", MACHINE_NO_SOUND_HW )
