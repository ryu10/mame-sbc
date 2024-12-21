STANDALONE = true

CPUS["M6502"] = true

-- MACHINES["Z80DAISY"] = true

function standalone()
	files{
		MAME_DIR .. "src/pldr6502/main.cpp",
		MAME_DIR .. "src/pldr6502/pldr6502.cpp",
		MAME_DIR .. "src/pldr6502/pldr6502.h",
		MAME_DIR .. "src/pldr6502/interface.h",
	}
end

