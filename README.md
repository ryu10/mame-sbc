# mame-sbc ... A shrunk mame-package for SBC/RetroCPU developers

> * [Japanese README is here](README_ja.md)
> * [Install & Run process is here(Sorry, Japanese only)](INSTALL.md)

A trial to build a SBC emulator, with CPU/IO companion processor Single Board Computer(SBC).  Theare two key items, CPU, and a serial interface for SBC console.  No video/audio devices are needed, therefore omitted.  Floppy software emulator on SD card are appreciated, so far not yet be ready.

Now I am trying to prepare a shrunk mame package with various CPU and some.

# Original

The **mame** package resides on https://github.com/mamedev/mame .  They say;

> MAME is a multi-purpose emulation framework.
> 
> MAME's purpose is to preserve decades of software history. As electronic technology continues to rush forward, MAME prevents this important "vintage" software from being lost and forgotten. This is achieved by documenting the hardware and how it functions. The source code to MAME serves as this documentation. The fact that the software is usable serves primarily to validate the accuracy of the documentation (how else can you prove that you have recreated the hardware faithfully?). Over time, MAME (originally stood for Multiple Arcade Machine Emulator) absorbed the sister-project MESS (Multi Emulator Super System), so MAME now documents a wide variety of (mostly vintage) computers, video game consoles and calculators, in addition to the arcade video games that were its initial focus.

