STANDALONE = true

CPUS["Z80"] = true

MACHINES["Z80DAISY"] = true

MACHINES["UART_I8251"] = true

function standalone()
	files{
		MAME_DIR .. "src/sbc8080/main.cpp",
		MAME_DIR .. "src/sbc8080/sbc8080.cpp",
		MAME_DIR .. "src/sbc8080/sbc8080.h",
		MAME_DIR .. "src/sbc8080/interface.h",
	}
end

