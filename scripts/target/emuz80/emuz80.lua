STANDALONE = true

CPUS["Z80"] = true

MACHINES["Z80DAISY"] = true

function standalone()
	files{
		MAME_DIR .. "src/emuz80/main.cpp",
		MAME_DIR .. "src/emuz80/emuz80.cpp",
		MAME_DIR .. "src/emuz80/emuz80.h",
		MAME_DIR .. "src/emuz80/interface.h",
		MAME_DIR .. "src/emuz80/osd.h",
		MAME_DIR .. "src/emuz80/osd_linux.c",
	}
end

