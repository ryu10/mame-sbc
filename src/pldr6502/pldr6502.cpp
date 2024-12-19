// license:BSD-3-Clause
// copyright-holders:Jonathan Gevaryahu, Robbbert, Miodrag Milanovic
/******************************************************************************

  This is a simplified version of the pldr6502 driver, merely as an example for a standalone
  emulator build. Video terminal and user interface is removed. For full notes and proper
  emulation driver, see src/mame/homebrew/pldr6502.cpp.

******************************************************************************/

#define P_M6502 0
#define P_R65C02 1
#define P_W65C02S 2
#define P_RP2A03 3
#ifndef P65TYPE
// Choose one from above
#define P65TYPE P_W65C02S
#endif


#include "emu.h"

#if P65TYPE == P_R65C02
#include "cpu/m6502/r65c02.h"
#elif P65TYPE == P_W65C02S
#include "cpu/m6502/w65c02s.h"
#elif P65TYPE == P_RP2A03
#include "cpu/m6502/rp2a03.h"
#else 
#include "cpu/m6502/m6502.h"
#endif

#include "pldr6502.h"
#include "interface.h"
#include "machine/uart_tty.h"

#include <cstdio>
#include <cstdlib>

class pldr6502_state : public driver_device
{
public:
	pldr6502_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_main_ram(*this, "main_ram"),
		m_main_rom(*this, "main_rom"),
		m_uart(*this, "uart")
	{
		fprintf(stderr, "pldr6502_state: constructor\n");
	}

	uint8_t uart_creg_r();
	uint8_t uart_dreg_r();
	void uart_creg_w(uint8_t data);
	void uart_dreg_w(uint8_t data);
	// void display_w(offs_t offset, uint8_t data);

	void m68_mem(address_map &map) ATTR_COLD;
	// void io_map(address_map &map) ATTR_COLD;
	void pldr6502(machine_config &config);

private:
	required_device<cpu_device> m_maincpu;
	required_shared_ptr<uint8_t> m_main_ram;
	required_shared_ptr<uint8_t> m_main_rom;
	required_device<uart_device> m_uart;

	virtual void machine_reset() override ATTR_COLD;
};


/******************************************************************************
 Machine Start/Reset
******************************************************************************/

void pldr6502_state::machine_reset()
{

	// program is self-modifying, so need to refresh it on each run
	memcpy(m_main_rom, pldr6502_binary, sizeof pldr6502_binary);
	fprintf(stderr, "memcpy: %ld bytes to main_rom\n", sizeof pldr6502_binary);
	fprintf(stderr, "reset vector: %02X %02X \n", m_main_rom[0xfffd - 0xe000], m_main_rom[0xfffc - 0xe000]);
	fprintf(stderr, "machine_reset\n");

}


/******************************************************************************
 I/O Handlers
******************************************************************************/

uint8_t pldr6502_state::uart_dreg_r() { return m_uart->data_r(); }
void    pldr6502_state::uart_dreg_w(uint8_t data) { m_uart->data_w(data); }
uint8_t pldr6502_state::uart_creg_r() {	return m_uart->status_r(); }
void    pldr6502_state::uart_creg_w(uint8_t data) {
	// fprintf(stderr, "uart_creg_w: %02x\n", data);
}

/******************************************************************************
 Address Maps
******************************************************************************/

void pldr6502_state::m68_mem(address_map &map)
{
	map(0x0000, 0x7fff).ram().share("main_ram");
	map(0x8018, 0x8018).rw(FUNC(pldr6502_state::uart_creg_r), FUNC(pldr6502_state::uart_creg_w));
	map(0x8019, 0x8019).rw(FUNC(pldr6502_state::uart_dreg_r), FUNC(pldr6502_state::uart_dreg_w));
	map(0xe000, 0xffff).rom().share("main_rom");
}

/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( pldr6502 )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void pldr6502_state::pldr6502(machine_config &config)
{
	/* basic machine hardware */
#if P65TYPE == P_R65C02
	R65C02(config, m_maincpu, XTAL(16'000'000) / 4);
#elif P65TYPE == P_W65C02S
	W65C02S(config, m_maincpu, XTAL(16'000'000) / 4);
#elif P65TYPE == P_RP2A03
	RP2A03_CORE(config, m_maincpu, XTAL(16'000'000) / 4);
#else 
	M6502(config, m_maincpu, XTAL(16'000'000) / 4);
#endif
	UART(config, m_uart, 9600);
	m_maincpu->set_addrmap(AS_PROGRAM, &pldr6502_state::m68_mem);
}


/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START(pldr6502)
	ROM_REGION(0x0, "maincpu", 0)
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT      COMPAT  MACHINE   INPUT   STATE         INIT        COMPANY                         FULLNAME                            FLAGS */
COMP( 2024, pldr6502,   0,          0,      pldr6502,   pldr6502, pldr6502_state, empty_init, "VintageChips, Houmei", "pldr6502 (6502+6850)", MACHINE_NO_SOUND_HW )
