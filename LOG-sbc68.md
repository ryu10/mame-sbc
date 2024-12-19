# sbc6800/sbc6809/pldr6502 作成ログ

この項は @ryu10 が記述しました。

## ターゲットのビルド手順

`makefile` の次のいずれか 1 行をコメント解除します。

```
# TARGET = sbc8080
# TARGET = emuz80
TARGET = sbc6800
# TARGET = sbc6809
# TARGET = pldr6502
```

その後、`mame-sbc` ディレクトリ直下で `mame -j5` を実行します。ビルド環境のコア数に合わせて数値 `5` を調節します。

詳細は [INSTALL.md](/INSTALL.md) を参照してください。

## sbc6800

電脳伝説 @vintagechips 様作 sbc6800 のエミュレータです。Mikbug が起動します。

* メインディレクトリ: [/src/sbc6800](/src/sbc6800)
* ビルドスクリプト: `scripts/target/sbc6800/sbc6800.lua`
* m6800 CPU コード (本家 mame コミット [4358422](https://github.com/mamedev/mame/tree/4358422) から): `src/devices/cpu/m6800`

## sbc6809

電脳伝説 @vintagechips 様作 sbc6809 のエミュレータです。Basic が起動します。

* ファイル構成は `sbc6800` と同様
* `src/devices/cpu/m6809` 以下を本家 mame (コミット [4358422](https://github.com/mamedev/mame/tree/4358422) ) から復元

## pldr6502

ほうめい @houmei 様作 pldr6502 のエミュレータです。元々は sbc6800 のパイルダーカード (ドーターカード) として設計されています。Universal Monitor が起動します。

* ファイル構成は `sbc6800` と同様
* `src/devices/cpu/m6502` 以下を本家 mame (コミット [4358422](https://github.com/mamedev/mame/tree/4358422) ) から復元

## 作成手順

* `src/emuz80` をひな形に
* `src/sbc6800` 以下にマシンを記述
    * 起動時に RESET ピン操作が必要 (sbc6809, pldr6502 では不要)
* `src/devices/cpu/m6800` 以下を本家 mame から復元
    * 本家 mame のコミット [4358422](https://github.com/mamedev/mame/tree/4358422) を使用する (mame-sbc 系統がフォークしたコミットに十分近いと推測される)
* ビルドスクリプトを編集
    * `scripts/target/sbc6800/sbc6800.lua`
        * `emuz80.lua` をひな形に新規作成
    * `scripts/src/cpu.lua` 
        * m6800 関連行をコメント解除

## sbc6800 利用のヒント

* メモリマップは `src/sbc6800/sbc6800.cpp` の `sbc6800_state::m68_mem()` で定義されます。
* ROM の内容は `sbc6800_state::machine_reset()` 内の `memcpy()` 行で読み込まれます。
* ROM データは `src/sbc6800/sbc6800.h` で定義されています。内容は Mikbug と MPU リセットベクタです。

## pldr6502 の CPU 切り替え

`src/pldr6502/pldr6502.cpp` 冒頭付近の `#define P65TYPE` 行を編集してから pldr6502 を make します。

`src/devices/cpu/m6502` 以下を参照して他の 6502 バリアントを追加できるかもしれません。

## 作業環境

**開発環境** Ubuntu 24.04LTS 

**作業用フォークリポジトリ** https://github.com/ryu10/mame-sbc

**上流との差分** https://github.com/tendai22/mame-sbc/compare/v0.995...ryu10:mame-sbc:sbc68
