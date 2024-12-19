// license:BSD-3-Clause
// copyright-holders:Jonathan Gevaryahu, Robbbert, Miodrag Milanovic
/******************************************************************************

  This is a simplified version of the sbc6809 driver, merely as an example for a standalone
  emulator build. Video terminal and user interface is removed. For full notes and proper
  emulation driver, see src/mame/homebrew/sbc6809.cpp.

******************************************************************************/

#include "emu.h"
// #include "cpu/z80/z80.h"
#include "cpu/m6809/m6809.h"
#include "sbc6809.h"
#include "interface.h"
#include "machine/uart_tty.h"

#include <cstdio>
#include <cstdlib>

class sbc6809_state : public driver_device
{
public:
	sbc6809_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_main_ram(*this, "main_ram"),
		m_main_rom(*this, "main_rom"),
		m_uart(*this, "uart")
	{
		fprintf(stderr, "sbc6809_state: constructor\n");
	}

	uint8_t uart_creg_r();
	uint8_t uart_dreg_r();
	void uart_creg_w(uint8_t data);
	void uart_dreg_w(uint8_t data);

	void m68_mem(address_map &map) ATTR_COLD;
	// void io_map(address_map &map) ATTR_COLD;
	void sbc6809(machine_config &config);

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

void sbc6809_state::machine_reset()
{

	// program is self-modifying, so need to refresh it on each run
	#ifdef BASIC9
	memcpy(m_main_ram+0x70, sbc6809_b0_binary, sizeof sbc6809_b0_binary);
	fprintf(stderr, "memcpy: %ld bytes to main_ram\n", sizeof sbc6809_b0_binary);
	memcpy(m_main_rom, sbc6809_b1_binary, sizeof sbc6809_b1_binary);
	fprintf(stderr, "memcpy: %ld bytes to main_rom\n", sizeof sbc6809_b1_binary);
	#endif

	fprintf(stderr, "reset vector: %02X %02X \n", m_main_rom[0xfffe - 0xe000], m_main_rom[0xffff - 0xe000]);
	fprintf(stderr, "machine_reset\n");

}


/******************************************************************************
 I/O Handlers
******************************************************************************/

uint8_t sbc6809_state::uart_dreg_r() { return m_uart->data_r(); }
void    sbc6809_state::uart_dreg_w(uint8_t data) { m_uart->data_w(data); }
uint8_t sbc6809_state::uart_creg_r() {	return m_uart->status_r(); }
void    sbc6809_state::uart_creg_w(uint8_t data) {
	// fprintf(stderr, "uart_creg_w: %02x\n", data);
}

/******************************************************************************
 Address Maps
******************************************************************************/

void sbc6809_state::m68_mem(address_map &map)
{
	map(0x0000, 0x7fff).ram().share("main_ram");
	map(0x8018, 0x8018).rw(FUNC(sbc6809_state::uart_creg_r), FUNC(sbc6809_state::uart_creg_w));
	map(0x8019, 0x8019).rw(FUNC(sbc6809_state::uart_dreg_r), FUNC(sbc6809_state::uart_dreg_w));
	map(0xe000, 0xffff).rom().share("main_rom");
}


/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( sbc6809 )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void sbc6809_state::sbc6809(machine_config &config)
{
	/* basic machine hardware */
	MC6809(config, m_maincpu, XTAL(64'000'000));
	UART(config, m_uart, 9600);
	m_maincpu->set_addrmap(AS_PROGRAM, &sbc6809_state::m68_mem);
}


/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START(sbc6809)
	ROM_REGION(0x0, "maincpu", 0)
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT      COMPAT  MACHINE   INPUT   STATE         INIT        COMPANY                         FULLNAME                            FLAGS */
COMP( 2024, sbc6809,   0,          0,      sbc6809,   sbc6809, sbc6809_state, empty_init, "VintageChips", "sbc6809 (mc6809)", MACHINE_NO_SOUND_HW )
