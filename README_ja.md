# mame-sbc ... A shrunk mame-package for SBC/RetroCPU developers

> [English README is here](README.md)

mame-sbc は、シリアルI/O、CPU、ROM/RAM からなる Single Board Computer(SBC) のシミュレータです。キーとなるのはCPUとSBCコンソール用のシリアルインターフェースの2つです。 ビデオ/オーディオデバイスは不要なので省略。 SDカード上のフロッピーソフトエミュレータがあればありがたい。

mame-sbc は、ターゲットCPUのアセンブリ言語で書いたプログラム開発に使用するために開発されました。ターゲットCPUのプログラム(HEXファイルなど)をロード、実行する機能を持ちます。

mame-sbc は、ターゲットボードごとに固有の実行可能バイナリを持つコンソールアプリケーションです。現在は Linux (Ubuntu on WSL)上で動作・開発しています。

さまざまなレトロCPUに容易に対応できるように、多くのCPUに対応しているエミュレータである mame をベースとしました。mame はゲームコンソールも対応している高機能のソフトウェアエミュレータです。あまりに多くの機能とライブラリを持つために、本パッケージではコンソールアプリケーションとシリアルI/Oだけを使用することを前提に削り落とすことを試みました。

現在のところ、レトロCPU界隈で有名なSBC 2つ、emuz80 と sbc8080 のエミュレータが動作可能です。それぞれで動作する通信テストプログラムとBASICインタプリタの動作を確認しています。BASICインタプリタを動作させた際には、ASCIIART.BASの実行が可能です。

# Original

The **mame** package resides on https://github.com/mamedev/mame .  They say;

> MAME is a multi-purpose emulation framework.
> 
> MAME's purpose is to preserve decades of software history. As electronic technology continues to rush forward, MAME prevents this important "vintage" software from being lost and forgotten. This is achieved by documenting the hardware and how it functions. The source code to MAME serves as this documentation. The fact that the software is usable serves primarily to validate the accuracy of the documentation (how else can you prove that you have recreated the hardware faithfully?). Over time, MAME (originally stood for Multiple Arcade Machine Emulator) absorbed the sister-project MESS (Multi Emulator Super System), so MAME now documents a wide variety of (mostly vintage) computers, video game consoles and calculators, in addition to the arcade video games that were its initial focus.

