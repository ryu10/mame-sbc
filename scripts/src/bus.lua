-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   bus.lua
--
--   Rules for building bus cores
--
---------------------------------------------------------------------------


---------------------------------------------------
--
--@src/devices/bus/rc2014/rc2014.h,BUSES["RC2014"] = true
---------------------------------------------------

if (BUSES["RC2014"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/rc2014/rc2014.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/rc2014.h",
		--MAME_DIR .. "src/devices/bus/rc2014/cf.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/cf.h",
		MAME_DIR .. "src/devices/bus/rc2014/clock.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/clock.h",
		MAME_DIR .. "src/devices/bus/rc2014/edge.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/edge.h",
		--MAME_DIR .. "src/devices/bus/rc2014/fdc.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/fdc.h",
		--MAME_DIR .. "src/devices/bus/rc2014/ide.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/ide.h",
		--MAME_DIR .. "src/devices/bus/rc2014/micro.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/micro.h",
		MAME_DIR .. "src/devices/bus/rc2014/modules.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/modules.h",
		MAME_DIR .. "src/devices/bus/rc2014/ram.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/ram.h",
		MAME_DIR .. "src/devices/bus/rc2014/rom.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/rom.h",
		--MAME_DIR .. "src/devices/bus/rc2014/romram.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/romram.h",
		MAME_DIR .. "src/devices/bus/rc2014/rtc.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/rtc.h",
		--MAME_DIR .. "src/devices/bus/rc2014/serial.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/serial.h",
		--MAME_DIR .. "src/devices/bus/rc2014/z180cpu.cpp",
		--MAME_DIR .. "src/devices/bus/rc2014/z180cpu.h",
		MAME_DIR .. "src/devices/bus/rc2014/z80cpu.cpp",
		MAME_DIR .. "src/devices/bus/rc2014/z80cpu.h",
	}
end

---------------------------------------------------
--
--@src/devices/bus/s100/s100.h,BUSES["S100"] = true
---------------------------------------------------

if (BUSES["S100"]~=null) then
	files {
--		MAME_DIR .. "src/devices/bus/s100/s100.cpp",
--		MAME_DIR .. "src/devices/bus/s100/s100.h",
--		MAME_DIR .. "src/devices/bus/s100/mm65k16s.cpp",
--		MAME_DIR .. "src/devices/bus/s100/mm65k16s.h",
--		MAME_DIR .. "src/devices/bus/s100/nsmdsa.cpp",
--		MAME_DIR .. "src/devices/bus/s100/nsmdsa.h",
--		MAME_DIR .. "src/devices/bus/s100/nsmdsad.cpp",
--		MAME_DIR .. "src/devices/bus/s100/nsmdsad.h",
--		MAME_DIR .. "src/devices/bus/s100/poly16k.cpp",
--		MAME_DIR .. "src/devices/bus/s100/poly16k.h",
--		MAME_DIR .. "src/devices/bus/s100/seals8k.cpp",
--		MAME_DIR .. "src/devices/bus/s100/seals8k.h",
	}
end

---------------------------------------------------
--
--@src/devices/bus/rs232/rs232.h,BUSES["RS232"] = true
---------------------------------------------------

if (BUSES["RS232"]~=null) then
	files {
--		MAME_DIR .. "src/devices/bus/rs232/keyboard.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/keyboard.h",
--		MAME_DIR .. "src/devices/bus/rs232/loopback.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/loopback.h",
--		MAME_DIR .. "src/devices/bus/rs232/null_modem.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/null_modem.h",
--		MAME_DIR .. "src/devices/bus/rs232/pty.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/pty.h",
--		MAME_DIR .. "src/devices/bus/rs232/rs232.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/rs232.h",
--		MAME_DIR .. "src/devices/bus/rs232/rs232_sync_io.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/rs232_sync_io.h",
--		MAME_DIR .. "src/devices/bus/rs232/terminal.cpp",
--		MAME_DIR .. "src/devices/bus/rs232/terminal.h",
	}
end


---------------------------------------------------
--
--@src/devices/bus/sdk85/memexp.h,BUSES["SDK85"] = true
---------------------------------------------------

if (BUSES["SDK85"]~=null) then
	files {
--		MAME_DIR .. "src/devices/bus/sdk85/memexp.cpp",
--		MAME_DIR .. "src/devices/bus/sdk85/memexp.h",
--		MAME_DIR .. "src/devices/bus/sdk85/i8755.cpp",
--		MAME_DIR .. "src/devices/bus/sdk85/i8755.h",
	}
end


---------------------------------------------------
--
--@src/devices/bus/mc68000/sysbus.h,BUSES["MC68000_SYSBUS"] = true
---------------------------------------------------

if (BUSES["MC68000_SYSBUS"]~=null) then
	files {
--		MAME_DIR .. "src/devices/bus/mc68000/sysbus.cpp",
--		MAME_DIR .. "src/devices/bus/mc68000/sysbus.h",
--		MAME_DIR .. "src/devices/bus/mc68000/cards.cpp",
--		MAME_DIR .. "src/devices/bus/mc68000/cards.h",
--		MAME_DIR .. "src/devices/bus/mc68000/floppy.cpp",
--		MAME_DIR .. "src/devices/bus/mc68000/floppy.h",
--		MAME_DIR .. "src/devices/bus/mc68000/ram.cpp",
--		MAME_DIR .. "src/devices/bus/mc68000/ram.h",
	}
end

