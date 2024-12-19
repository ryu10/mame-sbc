STANDALONE = true

CPUS["Z80"] = true

MACHINES["Z80DAISY"] = false

MACHINES["I8251"] = false

function standalone()
	files{
		MAME_DIR .. "src/test/main.cpp",
		--MAME_DIR .. "src/test/test.cpp",
		--MAME_DIR .. "src/test/test_emuz80.cpp",
		MAME_DIR .. "src/test/test_sbc8080.cpp",
		MAME_DIR .. "src/test/test.h",
		--MAME_DIR .. "src/test/uart_tty.h",
		--MAME_DIR .. "src/test/uart_tty.cpp",
		--MAME_DIR .. "src/test/tty.h",
		--MAME_DIR .. "src/test/tty.cpp",
		--MAME_DIR .. "src/test/blink.h",
		--MAME_DIR .. "src/test/blink.cpp",
	}
end

