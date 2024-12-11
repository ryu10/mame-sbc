STANDALONE = true

CPUS["Z80"] = true

MACHINES["Z80DAISY"] = false

function standalone()
	files{
		MAME_DIR .. "src/i8251_test/main.cpp",
		MAME_DIR .. "src/i8251_test/i8251_test.cpp",
		MAME_DIR .. "src/i8251_test/i8251_test.h",
		MAME_DIR .. "src/i8251_test/interface.h",
		MAME_DIR .. "src/i8251_test/tty.h",
		MAME_DIR .. "src/i8251_test/tty.cpp",
	}
end

