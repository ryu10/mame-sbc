-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   machine.lua
--
--   Rules for building machine cores
--
----------------------------------------------------------------------------

files {
	MAME_DIR .. "src/devices/machine/clock.cpp",
	MAME_DIR .. "src/devices/machine/clock.h",
	MAME_DIR .. "src/devices/machine/keyboard.cpp",
	MAME_DIR .. "src/devices/machine/keyboard.h",
	MAME_DIR .. "src/devices/machine/keyboard.ipp",
	MAME_DIR .. "src/devices/machine/ram.cpp",
	MAME_DIR .. "src/devices/machine/ram.h",
	MAME_DIR .. "src/devices/machine/terminal.cpp",
	MAME_DIR .. "src/devices/machine/terminal.h",
}
files {
--	MAME_DIR .. "src/devices/imagedev/bitbngr.cpp",
--	MAME_DIR .. "src/devices/imagedev/bitbngr.h",
--	MAME_DIR .. "src/devices/imagedev/cartrom.cpp",
--	MAME_DIR .. "src/devices/imagedev/cartrom.h",
--	MAME_DIR .. "src/devices/imagedev/cassette.cpp",
--	MAME_DIR .. "src/devices/imagedev/cassette.h",
--	MAME_DIR .. "src/devices/imagedev/cdromimg.cpp",
--	MAME_DIR .. "src/devices/imagedev/cdromimg.h",
--	MAME_DIR .. "src/devices/imagedev/diablo.cpp",
--	MAME_DIR .. "src/devices/imagedev/diablo.h",
--	MAME_DIR .. "src/devices/imagedev/flopdrv.cpp",
--	MAME_DIR .. "src/devices/imagedev/flopdrv.h",
--	MAME_DIR .. "src/devices/imagedev/harddriv.cpp",
--	MAME_DIR .. "src/devices/imagedev/harddriv.h",
--	MAME_DIR .. "src/devices/imagedev/magtape.cpp",
--	MAME_DIR .. "src/devices/imagedev/magtape.h",
--	MAME_DIR .. "src/devices/imagedev/memcard.cpp",
--	MAME_DIR .. "src/devices/imagedev/memcard.h",
--	MAME_DIR .. "src/devices/imagedev/mfmhd.cpp",
--	MAME_DIR .. "src/devices/imagedev/mfmhd.h",
--	MAME_DIR .. "src/devices/imagedev/microdrv.cpp",
--	MAME_DIR .. "src/devices/imagedev/microdrv.h",
--	MAME_DIR .. "src/devices/imagedev/midiin.cpp",
--	MAME_DIR .. "src/devices/imagedev/midiin.h",
--	MAME_DIR .. "src/devices/imagedev/midiout.cpp",
--	MAME_DIR .. "src/devices/imagedev/midiout.h",
--	MAME_DIR .. "src/devices/imagedev/papertape.cpp",
--	MAME_DIR .. "src/devices/imagedev/papertape.h",
--	MAME_DIR .. "src/devices/imagedev/picture.cpp",
--	MAME_DIR .. "src/devices/imagedev/picture.h",
--	MAME_DIR .. "src/devices/imagedev/printer.cpp",
--	MAME_DIR .. "src/devices/imagedev/printer.h",
--	MAME_DIR .. "src/devices/imagedev/simh_tape_image.cpp",
--	MAME_DIR .. "src/devices/imagedev/simh_tape_image.h",
--	MAME_DIR .. "src/devices/imagedev/snapquik.cpp",
--	MAME_DIR .. "src/devices/imagedev/snapquik.h",
--	MAME_DIR .. "src/devices/imagedev/wafadrive.cpp",
--	MAME_DIR .. "src/devices/imagedev/wafadrive.h",
--	MAME_DIR .. "src/devices/imagedev/avivideo.cpp",
--	MAME_DIR .. "src/devices/imagedev/avivideo.h",
}


---------------------------------------------------
--
--@src/devices/machine/autoconfig.h,MACHINES["AUTOCONFIG"] = true
---------------------------------------------------

if (MACHINES["AUTOCONFIG"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/autoconfig.cpp",
		MAME_DIR .. "src/devices/machine/autoconfig.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/6522via.h,MACHINES["6522VIA"] = true
---------------------------------------------------

if (MACHINES["6522VIA"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/6522via.cpp",
		MAME_DIR .. "src/devices/machine/6522via.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/6821pia.h,MACHINES["6821PIA"] = true
---------------------------------------------------

if (MACHINES["6821PIA"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/6821pia.cpp",
		MAME_DIR .. "src/devices/machine/6821pia.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/6840ptm.h,MACHINES["6840PTM"] = true
---------------------------------------------------

if (MACHINES["6840PTM"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/6840ptm.cpp",
		MAME_DIR .. "src/devices/machine/6840ptm.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/6850acia.h,MACHINES["ACIA6850"] = true
---------------------------------------------------

if (MACHINES["ACIA6850"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/6850acia.cpp",
		MAME_DIR .. "src/devices/machine/6850acia.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/6883sam.h,MACHINES["6883SAM"] = true
---------------------------------------------------

if (MACHINES["6883SAM"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/6883sam.cpp",
		MAME_DIR .. "src/devices/machine/6883sam.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/8530scc.h,MACHINES["8530SCC"] = true
---------------------------------------------------

if (MACHINES["8530SCC"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/8530scc.cpp",
		MAME_DIR .. "src/devices/machine/8530scc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/am9517a.h,MACHINES["AM9517A"] = true
---------------------------------------------------

if (MACHINES["AM9517A"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/am9517a.cpp",
		MAME_DIR .. "src/devices/machine/am9517a.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/cdp1852.h,MACHINES["CDP1852"] = true
---------------------------------------------------

if (MACHINES["CDP1852"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/cdp1852.cpp",
		MAME_DIR .. "src/devices/machine/cdp1852.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/cdp1871.h,MACHINES["CDP1871"] = true
---------------------------------------------------

if (MACHINES["CDP1871"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/cdp1871.cpp",
		MAME_DIR .. "src/devices/machine/cdp1871.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/cdp1879.h,MACHINES["CDP1879"] = true
---------------------------------------------------

if (MACHINES["CDP1879"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/cdp1879.cpp",
		MAME_DIR .. "src/devices/machine/cdp1879.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ds1302.h,MACHINES["DS1302"] = true
---------------------------------------------------

if (MACHINES["DS1302"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/ds1302.cpp",
		MAME_DIR .. "src/devices/machine/ds1302.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/f3853.h,MACHINES["F3853"] = true
---------------------------------------------------

if (MACHINES["F3853"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/f3853.cpp",
		MAME_DIR .. "src/devices/machine/f3853.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/f4702.h,MACHINES["F4702"] = true
---------------------------------------------------

if (MACHINES["F4702"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/f4702.cpp",
		MAME_DIR .. "src/devices/machine/f4702.h",
	}
end


---------------------------------------------------
--
--@src/devices/machine/i8087.h,MACHINES["I8087"] = true
---------------------------------------------------

if (MACHINES["I8087"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8087.cpp",
--		MAME_DIR .. "src/devices/machine/i8087.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8155.h,MACHINES["I8155"] = true
---------------------------------------------------

if (MACHINES["I8155"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8155.cpp",
--		MAME_DIR .. "src/devices/machine/i8155.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8212.h,MACHINES["I8212"] = true
---------------------------------------------------

if (MACHINES["I8212"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8212.cpp",
--		MAME_DIR .. "src/devices/machine/i8212.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8214.h,MACHINES["I8214"] = true
---------------------------------------------------

if (MACHINES["I8214"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8214.cpp",
--		MAME_DIR .. "src/devices/machine/i8214.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i82355.h,MACHINES["I82355"] = true
---------------------------------------------------

if (MACHINES["I82355"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i82355.cpp",
--		MAME_DIR .. "src/devices/machine/i82355.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8243.h,MACHINES["I8243"] = true
---------------------------------------------------

if (MACHINES["I8243"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8243.cpp",
--		MAME_DIR .. "src/devices/machine/i8243.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8251.h,MACHINES["I8251"] = true
---------------------------------------------------

if (MACHINES["I8251"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8251.cpp",
--		MAME_DIR .. "src/devices/machine/i8251.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8257.h,MACHINES["I8257"] = true
---------------------------------------------------

if (MACHINES["I8257"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8257.cpp",
--		MAME_DIR .. "src/devices/machine/i8257.h",
	}
end


---------------------------------------------------
--
--@src/devices/machine/i8271.h,MACHINES["I8271"] = true
---------------------------------------------------

if (MACHINES["I8271"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8271.cpp",
--		MAME_DIR .. "src/devices/machine/i8271.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8279.h,MACHINES["I8279"] = true
---------------------------------------------------

if (MACHINES["I8279"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8279.cpp",
--		MAME_DIR .. "src/devices/machine/i8279.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8355.h,MACHINES["I8355"] = true
---------------------------------------------------

if (MACHINES["I8355"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8355.cpp",
--		MAME_DIR .. "src/devices/machine/i8355.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i80130.h,MACHINES["I80130"] = true
---------------------------------------------------

if (MACHINES["I80130"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i80130.cpp",
--		MAME_DIR .. "src/devices/machine/i80130.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ins8154.h,MACHINES["INS8154"] = true
---------------------------------------------------

if (MACHINES["INS8154"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ins8154.cpp",
--		MAME_DIR .. "src/devices/machine/ins8154.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ins8250.h,MACHINES["INS8250"] = true
---------------------------------------------------

if (MACHINES["INS8250"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ins8250.cpp",
--		MAME_DIR .. "src/devices/machine/ins8250.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc6843.h,MACHINES["MC6843"] = true
---------------------------------------------------

if (MACHINES["MC6843"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc6843.cpp",
--		MAME_DIR .. "src/devices/machine/mc6843.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc6844.h,MACHINES["MC6844"] = true
---------------------------------------------------

if (MACHINES["MC6844"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc6844.cpp",
--		MAME_DIR .. "src/devices/machine/mc6844.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc6846.h,MACHINES["MC6846"] = true
---------------------------------------------------

if (MACHINES["MC6846"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc6846.cpp",
--		MAME_DIR .. "src/devices/machine/mc6846.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc6852.h,MACHINES["MC6852"] = true
---------------------------------------------------

if (MACHINES["MC6852"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc6852.cpp",
--		MAME_DIR .. "src/devices/machine/mc6852.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc6854.h,MACHINES["MC6854"] = true
---------------------------------------------------

if (MACHINES["MC6854"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc6854.cpp",
--		MAME_DIR .. "src/devices/machine/mc6854.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc68328.h,MACHINES["MC68328"] = true
---------------------------------------------------

if (MACHINES["MC68328"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc68328.cpp",
--		MAME_DIR .. "src/devices/machine/mc68328.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc68901.h,MACHINES["MC68901"] = true
---------------------------------------------------

if (MACHINES["MC68901"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc68901.cpp",
--		MAME_DIR .. "src/devices/machine/mc68901.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos6526.h,MACHINES["MOS6526"] = true
---------------------------------------------------

if (MACHINES["MOS6526"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos6526.cpp",
--		MAME_DIR .. "src/devices/machine/mos6526.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos6529.h,MACHINES["MOS6529"] = true
---------------------------------------------------

if (MACHINES["MOS6529"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos6529.cpp",
--		MAME_DIR .. "src/devices/machine/mos6529.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos6530.h,MACHINES["MOS6530"] = true
---------------------------------------------------

if (MACHINES["MOS6530"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos6530.cpp",
--		MAME_DIR .. "src/devices/machine/mos6530.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos6702.h,MACHINES["MOS6702"] = true
---------------------------------------------------

if (MACHINES["MOS6702"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos6702.cpp",
--		MAME_DIR .. "src/devices/machine/mos6702.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos8706.h,MACHINES["MOS8706"] = true
---------------------------------------------------

if (MACHINES["MOS8706"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos8706.cpp",
--		MAME_DIR .. "src/devices/machine/mos8706.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos8722.h,MACHINES["MOS8722"] = true
---------------------------------------------------

if (MACHINES["MOS8722"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos8722.cpp",
--		MAME_DIR .. "src/devices/machine/mos8722.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos8726.h,MACHINES["MOS8726"] = true
---------------------------------------------------

if (MACHINES["MOS8726"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos8726.cpp",
--		MAME_DIR .. "src/devices/machine/mos8726.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mos6551.h,MACHINES["MOS6551"] = true
---------------------------------------------------

if (MACHINES["MOS6551"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mos6551.cpp",
--		MAME_DIR .. "src/devices/machine/mos6551.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/pla.h,MACHINES["PLA"] = true
---------------------------------------------------

if (MACHINES["PLA"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/pla.cpp",
--		MAME_DIR .. "src/devices/machine/pla.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/sc16is741.h,MACHINES["SC16IS741"] = true
---------------------------------------------------
if (MACHINES["SC16IS741"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/sc16is741.cpp",
--		MAME_DIR .. "src/devices/machine/sc16is741.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/tms9901.h,MACHINES["TMS9901"] = true
---------------------------------------------------

if (MACHINES["TMS9901"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/tms9901.cpp",
--		MAME_DIR .. "src/devices/machine/tms9901.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/tms9902.h,MACHINES["TMS9902"] = true
---------------------------------------------------

if (MACHINES["TMS9902"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/tms9902.cpp",
--		MAME_DIR .. "src/devices/machine/tms9902.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/tms9914.h,MACHINES["TMS9914"] = true
---------------------------------------------------

if (MACHINES["TMS9914"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/tms9914.cpp",
--		MAME_DIR .. "src/devices/machine/tms9914.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/upd765.h,MACHINES["UPD765"] = true
---------------------------------------------------

if (MACHINES["UPD765"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/upd765.cpp",
--		MAME_DIR .. "src/devices/machine/upd765.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/vic_pl192.h,MACHINES["VIC_PL192"] = true
---------------------------------------------------

if (MACHINES["VIC_PL192"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/vic_pl192.cpp",
--		MAME_DIR .. "src/devices/machine/vic_pl192.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/wd_fdc.h,MACHINES["WD_FDC"] = true
---------------------------------------------------

if (MACHINES["WD_FDC"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/wd_fdc.cpp",
--		MAME_DIR .. "src/devices/machine/wd_fdc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80ctc.h,MACHINES["Z80CTC"] = true
---------------------------------------------------

if (MACHINES["Z80CTC"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80ctc.cpp",
		MAME_DIR .. "src/devices/machine/z80ctc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80sio.h,MACHINES["Z80SIO"] = true
---------------------------------------------------

if (MACHINES["Z80SIO"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80sio.cpp",
		MAME_DIR .. "src/devices/machine/z80sio.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80scc.h,MACHINES["Z80SCC"] = true
---------------------------------------------------

if (MACHINES["Z80SCC"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80scc.cpp",
		MAME_DIR .. "src/devices/machine/z80scc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80dma.h,MACHINES["Z80DMA"] = true
---------------------------------------------------

if (MACHINES["Z80DMA"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80dma.cpp",
		MAME_DIR .. "src/devices/machine/z80dma.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80pio.h,MACHINES["Z80PIO"] = true
---------------------------------------------------

if (MACHINES["Z80PIO"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80pio.cpp",
		MAME_DIR .. "src/devices/machine/z80pio.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80sti.h,MACHINES["Z80STI"] = true
---------------------------------------------------

if (MACHINES["Z80STI"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80sti.cpp",
		MAME_DIR .. "src/devices/machine/z80sti.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z8536.h,MACHINES["Z8536"] = true
---------------------------------------------------

if (MACHINES["Z8536"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/z8536.cpp",
--		MAME_DIR .. "src/devices/machine/z8536.h",
	}
end

--@src/devices/machine/intelfsh.h,MACHINES["INTELFLASH"] = true
if (MACHINES["INTELFLASH"]~=null) then
	files {
--        MAME_DIR .. "src/devices/machine/intelfsh.cpp",
--      MAME_DIR .. "src/devices/machine/intelfsh.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mpu401.h,MACHINES["MPU401"] = true
---------------------------------------------------

if (MACHINES["MPU401"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mpu401.cpp",
--		MAME_DIR .. "src/devices/machine/mpu401.h",
	}
end
---------------------------------------------------
--
--@src/devices/machine/diablo_hd.h,MACHINES["DIABLO_HD"] = true
---------------------------------------------------
if (MACHINES["DIABLO_HD"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/diablo_hd.cpp",
--		MAME_DIR .. "src/devices/machine/diablo_hd.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/fdc_pll.h,MACHINES["FDC_PLL"] = true
---------------------------------------------------

if (MACHINES["FDC_PLL"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/fdc_pll.cpp",
--		MAME_DIR .. "src/devices/machine/fdc_pll.h",
	}
end


---------------------------------------------------
--
--@src/devices/machine/input_merger.h,MACHINES["INPUT_MERGER"] = true
---------------------------------------------------
if (MACHINES["INPUT_MERGER"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/input_merger.cpp",
--		MAME_DIR .. "src/devices/machine/input_merger.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i82586.h,MACHINES["I82586"] = true
---------------------------------------------------

if (MACHINES["I82586"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i82586.cpp",
--		MAME_DIR .. "src/devices/machine/i82586.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/gen_fifo.h,MACHINES["GEN_FIFO"] = true
---------------------------------------------------

if (MACHINES["GEN_FIFO"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/gen_fifo.cpp",
--		MAME_DIR .. "src/devices/machine/gen_fifo.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z80daisy.h,MACHINES["Z80DAISY"] = true
---------------------------------------------------

if (MACHINES["Z80DAISY"]~=null) then
	files {
		MAME_DIR .. "src/devices/machine/z80daisy.cpp",
		MAME_DIR .. "src/devices/machine/z80daisy.h",
		MAME_DIR .. "src/devices/machine/z80daisy_generic.cpp",
		MAME_DIR .. "src/devices/machine/z80daisy_generic.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/i8291a.h,MACHINES["I8291A"] = true
---------------------------------------------------

if (MACHINES["I8291A"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i8291a.cpp",
--		MAME_DIR .. "src/devices/machine/i8291a.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2dma.h,MACHINES["PS2DMAC"] = true
---------------------------------------------------

if (MACHINES["PS2DMAC"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2dma.cpp",
--		MAME_DIR .. "src/devices/machine/ps2dma.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2intc.h,MACHINES["PS2INTC"] = true
---------------------------------------------------

if (MACHINES["PS2INTC"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2intc.cpp",
--		MAME_DIR .. "src/devices/machine/ps2intc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2mc.h,MACHINES["PS2MC"] = true
---------------------------------------------------

if (MACHINES["PS2MC"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2mc.cpp",
--		MAME_DIR .. "src/devices/machine/ps2mc.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2pad.h,MACHINES["PS2PAD"] = true
---------------------------------------------------

if (MACHINES["PS2PAD"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2pad.cpp",
--		MAME_DIR .. "src/devices/machine/ps2pad.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2sif.h,MACHINES["PS2SIF"] = true
---------------------------------------------------

if (MACHINES["PS2SIF"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2sif.cpp",
--		MAME_DIR .. "src/devices/machine/ps2sif.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ps2timer.h,MACHINES["PS2TIMER"] = true
---------------------------------------------------

if (MACHINES["PS2TIMER"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ps2timer.cpp",
--		MAME_DIR .. "src/devices/machine/ps2timer.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/z8038.h,MACHINES["Z8038"] = true
---------------------------------------------------

if (MACHINES["Z8038"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/z8038.cpp",
--		MAME_DIR .. "src/devices/machine/z8038.h",
	}
end
---------------------------------------------------
--
--@src/devices/machine/i82357.h,MACHINES["I82357"] = true
---------------------------------------------------

if (MACHINES["I82357"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/i82357.cpp",
--		MAME_DIR .. "src/devices/machine/i82357.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ns32081.h,MACHINES["NS32081"] = true
---------------------------------------------------
if (MACHINES["NS32081"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ns32081.cpp",
--		MAME_DIR .. "src/devices/machine/ns32081.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ns32202.h,MACHINES["NS32202"] = true
---------------------------------------------------
if (MACHINES["NS32202"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ns32202.cpp",
--		MAME_DIR .. "src/devices/machine/ns32202.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ns32082.h,MACHINES["NS32082"] = true
---------------------------------------------------
if (MACHINES["NS32082"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ns32082.cpp",
--		MAME_DIR .. "src/devices/machine/ns32082.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/ns32382.h,MACHINES["NS32382"] = true
---------------------------------------------------
if (MACHINES["NS32382"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/ns32382.cpp",
--		MAME_DIR .. "src/devices/machine/ns32382.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/cammu.h,MACHINES["CAMMU"] = true
---------------------------------------------------
if (MACHINES["CAMMU"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/cammu.cpp",
--		MAME_DIR .. "src/devices/machine/cammu.h",
	}
end

---------------------------------------------------
--
--@src/devices/machine/mc88200.h,MACHINES["MC88200"] = true
---------------------------------------------------
if (MACHINES["MC88200"]~=null) then
	files {
--		MAME_DIR .. "src/devices/machine/mc88200.cpp",
--		MAME_DIR .. "src/devices/machine/mc88200.h",
	}
end

