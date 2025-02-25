# sbc6800/sbc6809/pldr6502 作業メモ

この項は @ryu10 が記述しました。

## ターゲット指定とビルド

`makefile` の次のいずれか 1 行をコメント解除します。

```
# TARGET = sbc8080
# TARGET = emuz80
TARGET = sbc6800
# TARGET = sbc6809
# TARGET = pldr6502
```

その後、`mame-sbc` トップディレクトリで `mame -j5` を実行します。ビルド環境のコア数に合わせて数値 `5` を調節します。詳細は [INSTALL.md](/INSTALL.md) を参照してください。

## sbc6800

電脳伝説 @vintagechips 様作 SBC6800 のエミュレータです。Mikbug が起動します。

* マシン記述: [src/sbc6800](src/sbc6800)
* m6800 プロセッサ: [src/devices/cpu/m6800](src/devices/cpu/m6800) 
* ビルドスクリプト: [scripts/target/sbc6800/sbc6800.lua](scripts/target/sbc6800/sbc6800.lua), [scripts/src/cpu.lua](scripts/src/cpu.lua)

### sbc6800 利用のヒント

* メモリマップは [src/sbc6800/sbc6800.cpp](src/sbc6800/sbc6800.cpp) の `sbc6800_state::m68_mem()` で定義されます。
* ROM の内容は `sbc6800_state::machine_reset()` 内の `memcpy()` 行で読み込まれます。
* ROM データは [src/sbc6800/sbc6800.h](src/sbc6800/sbc6800.h) で定義されています。内容は Mikbug と MPU リセットベクタです。
* `hexdump` コマンドを使って、ROM の bin ファイルから C の hex 配列 (の要素部分) を生成できます。

```
hexdump -v -e '8/1 "0x%02x, " "\n"' unimon.bin > unimon_c_hex.txt
```

### sbc6800 作成手順

* [src/emuz80](src/emuz80) をひな形に
* [src/sbc6800](src/sbc6800) 以下にマシンを記述
    * 起動時に RESET ピン操作が必要 (sbc6809, pldr6502 では不要)
* [src/devices/cpu/m6800](src/devices/cpu/m6800) 以下を本家 mame から復元
    * 本家 mame のコミット [4358422](https://github.com/mamedev/mame/tree/4358422) を使用する (mame-sbc 系統がフォークしたコミットに十分近いと推測される)
* ビルドスクリプトを編集
    * [scripts/target/sbc6800/sbc6800.lua](scripts/target/sbc6800/sbc6800.lua) (新規作成)
    * [scripts/src/cpu.lua](scripts/src/cpu.lua) (m6800 関連行をコメント解除)

## sbc6809

電脳伝説 @vintagechips 様作 SBC6809 のエミュレータです。Basic が起動します。

* ファイル構成は sbc6800 と同様
* [src/devices/cpu/m6809](src/devices/cpu/m6809) 以下を本家 mame から復元

## pldr6502

ほうめい @houmei 様作 PLDR6502 のエミュレータです。元々は SBC6800 のドータカード (パイルダーカード) として設計されています。Universal Monitor が起動します。

* ファイル構成は sbc6800 と同様
* [src/devices/cpu/m6502](src/devices/cpu/m6502) 以下を本家 mame から復元

### pldr6502 の CPU 切り替え

[src/pldr6502/pldr6502.cpp](src/pldr6502/pldr6502.cpp) 冒頭付近の `#define P65TYPE` 行を編集してから pldr6502 を make します。

[src/devices/cpu/m6502](src/devices/cpu/m6502) 以下を参照して他の 6502 バリアントを追加できるかもしれません。

## 作業環境

**開発環境** Ubuntu 24.04LTS 

**作業用フォークリポジトリ** https://github.com/ryu10/mame-sbc

**上流との差分** https://github.com/tendai22/mame-sbc/compare/v0.995...ryu10:mame-sbc:sbc68
