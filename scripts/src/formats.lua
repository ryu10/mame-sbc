-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   formats.lua
--
--   Rules for building formats
--
---------------------------------------------------------------------------
function formatsProject(_target, _subtarget)
project "formats"
	uuid (os.uuid("formats-" .. _target .."_" .. _subtarget))
	kind (LIBTYPE)
	targetsubdir(_target .."_" .. _subtarget)
	addprojectflags()

	options {
		"ArchiveSplit",
	}

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		GEN_DIR,
		ext_includedir("flac"),
		ext_includedir("zlib"),
	}

	files {
		MAME_DIR .. "src/lib/formats/all.cpp",
		MAME_DIR .. "src/lib/formats/all.h",

--		MAME_DIR .. "src/lib/formats/imageutl.cpp",
--		MAME_DIR .. "src/lib/formats/imageutl.h",

--		MAME_DIR .. "src/lib/formats/pc_dsk.cpp",
--		MAME_DIR .. "src/lib/formats/pc_dsk.h",
--		MAME_DIR .. "src/lib/formats/fdi_dsk.cpp",

--		MAME_DIR .. "src/lib/formats/fsmgr.h",
--		MAME_DIR .. "src/lib/formats/fsmgr.cpp",
	}

--------------------------------------------------
--
--@src/lib/formats/os9_dsk.h,FORMATS["OS9_DSK"] = true
--------------------------------------------------

if opt_tool(FORMATS, "OS9_DSK") then
	files {
--		MAME_DIR.. "src/lib/formats/os9_dsk.cpp",
--		MAME_DIR.. "src/lib/formats/os9_dsk.h",
	}
end

--------------------------------------------------
--
--@src/lib/formats/kim1_cas.h,FORMATS["KIM1_CAS"] = true
--------------------------------------------------

if opt_tool(FORMATS, "KIM1_CAS") then
	files {
--		MAME_DIR.. "src/lib/formats/kim1_cas.cpp",
--		MAME_DIR.. "src/lib/formats/kim1_cas.h",
	}
end

--------------------------------------------------
--
--@src/lib/formats/mdos_dsk.h,FORMATS["MDOS_DSK"] = true
--------------------------------------------------

if opt_tool(FORMATS, "MDOS_DSK") then
	files {
--		MAME_DIR.. "src/lib/formats/mdos_dsk.cpp",
--		MAME_DIR.. "src/lib/formats/mdos_dsk.h",
	}
end

--------------------------------------------------
--
--@src/lib/formats/msx_dsk.h,FORMATS["MSX_DSK"] = true
--------------------------------------------------

if opt_tool(FORMATS, "MSX_DSK") then
	files {
--		MAME_DIR.. "src/lib/formats/msx_dsk.cpp",
--		MAME_DIR.. "src/lib/formats/msx_dsk.h",
	}
end

--------------------------------------------------
--
--@src/lib/formats/nascom_dsk.h,FORMATS["NASCOM_DSK"] = true
--------------------------------------------------

if opt_tool(FORMATS, "NASCOM_DSK") then
	files {
--		MAME_DIR.. "src/lib/formats/nascom_dsk.cpp",
--		MAME_DIR.. "src/lib/formats/nascom_dsk.h",
	}
end


--------------------------------------------------
--
--@src/lib/formats/wd177x_dsk.h,FORMATS["WD177X_DSK"] = true
--------------------------------------------------

if opt_tool(FORMATS, "WD177X_DSK") then
	files {
--		MAME_DIR.. "src/lib/formats/wd177x_dsk.cpp",
--		MAME_DIR.. "src/lib/formats/wd177x_dsk.h",
	}
end


--------------------------------------------------
--
--@src/lib/formats/fs_fat.h,FORMATS["FS_FAT"] = true
--------------------------------------------------

if opt_tool(FORMATS, "FS_FAT") then
	files {
--		MAME_DIR.. "src/lib/formats/fs_fat.cpp",
--		MAME_DIR.. "src/lib/formats/fs_fat.h",
	}
end


end
