// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai
/******************************************************************************

  An emulation for sbc8080, by @vintagechips (Den'noh-Densetsu),
  URL: https://vintagechips.wordpress.com/2018/06/24/sbc8080-cpu%E3%83%AB%E3%83%BC%E3%82%BA%E3%82%AD%E3%83%83%E3%83%88/

  It consists of 8080+8224+8228, ROM, RAM, and 8251.  It is a UART with 
  interrupt driven.
******************************************************************************/

#include "emu.h"	// for offs_t declaration
#include "cpu/z80/z80.h"
#include "sbc8080.h"
#include "interface.h"
#include "machine/uart_tty.h"

#include <cstdio>
#include <cstdlib>

/****************************************************************
 I8251 status_r 
******************************************************************/
DECLARE_DERIVED_UART_DEVICE(UART_I8251, uart_i8251_device)

uint8_t uart_i8251_device::update_status_r(void)
{
    // compose bits of status register
#define TXEMPTY_Bit (1<<2)
#define RXRDY_Bit (1<<1)
#define TXRDY_Bit (1<<0)
    uint8_t c = 0;
    if (m_data_r_ready) {
        c |= RXRDY_Bit;
	}
    if (m_data_w_ready == 0 && m_data_w_empty == 1) {
        c |= TXRDY_Bit;
	}
	if (m_data_w_empty == 1) {
		c |= TXEMPTY_Bit;
	}
	//fprintf(stderr, "(i8251:%02x)\n", c);
	return c;
}

DEFINE_DEVICE_TYPE(UART_I8251, uart_i8251_device, "uart_i8251", "uart_8251 on tty driver")



class sbc8080_state : public driver_device
{
public:
	sbc8080_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_main_ram(*this, "main_ram"),
		m_uart(*this, "uart_i8251")
	{
		fprintf(stderr, "sbc8080_state: constructor\n");
	}

	uint8_t uart_creg_r();
	uint8_t uart_dreg_r();
	void uart_creg_w(uint8_t data);
	void uart_dreg_w(uint8_t data);

	void z80_mem(address_map &map) ATTR_COLD;
	void io_map(address_map &map) ATTR_COLD;
	void sbc8080(machine_config &config);

	void sbc_int_w(int state);	// drive Z80 int line

private:
	required_device<z80_device> m_maincpu;
	required_shared_ptr<uint8_t> m_main_ram;
	required_device<uart_i8251_device> m_uart;

	virtual void machine_reset() override ATTR_COLD;

};

/******************************************************************************
 Machine Start/Reset
******************************************************************************/

void sbc8080_state::machine_reset()
{
	// program is self-modifying, so need to refresh it on each run
	memcpy(m_main_ram, sbc8080_binary, sizeof sbc8080_binary);
	fprintf(stderr, "machine_reset\n");
}


/******************************************************************************
 I/O Handlers
******************************************************************************/

uint8_t sbc8080_state::uart_dreg_r() { return m_uart->data_r(); }
void    sbc8080_state::uart_dreg_w(uint8_t data) { m_uart->data_w(data); }
uint8_t sbc8080_state::uart_creg_r() {	return m_uart->status_r(); }
void    sbc8080_state::uart_creg_w(uint8_t data) {
	//fprintf(stderr, "uart_creg_w: %02x\n", data);
}

/******************************************************************************
 Address Maps
******************************************************************************/

void sbc8080_state::z80_mem(address_map &map)
{
	map(0x0000, 0xffff).ram().share("main_ram");
}

void sbc8080_state::io_map(address_map &map)
{
	map.unmap_value_high();
	map.global_mask(0xff);
	map(0x00, 0x00).rw(FUNC(sbc8080_state::uart_dreg_r),FUNC(sbc8080_state::uart_dreg_w));
	map(0x01, 0x01).rw(FUNC(sbc8080_state::uart_creg_r),FUNC(sbc8080_state::uart_creg_w));

}

/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( sbc8080 )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void sbc8080_state::sbc8080(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(20'000'000));
	m_maincpu->set_addrmap(AS_PROGRAM, &sbc8080_state::z80_mem);
	m_maincpu->set_addrmap(AS_IO, &sbc8080_state::io_map);
	UART_I8251(config, m_uart, 9600);
	m_uart->rxrdy_handler().set(*this, FUNC(sbc8080_state::sbc_int_w));
}

/*
 * int handler
 */

void sbc8080_state::sbc_int_w(int state)
{
	m_maincpu->set_input_line(INPUT_LINE_IRQ0, state);
}
/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START(sbc8080)
	ROM_REGION(0x0, "maincpu", 0)
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT      COMPAT  MACHINE   INPUT   STATE         INIT        COMPANY                         FULLNAME                            FLAGS */
COMP( 2024, sbc8080,   0,          0,      sbc8080,   sbc8080, sbc8080_state, empty_init, "VintageChips", "sbc8080 (Z80 with PIC18F47Q53)", MACHINE_NO_SOUND_HW )
