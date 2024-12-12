# sbc6800/sbc6809 作成ログ

この項は @ryu10 が記述しました。

## sbc6800 と sbc6809 のビルド手順

`makefile` の次のいずれか 1 行をコメント解除します。

```
# TARGET = sbc8080
# TARGET = emuz80
TARGET = sbc6800
# TARGET = sbc6809
```

その後、`mame-sbc` ディレクトリ直下で `mame -j5` を実行します。

ビルド環境のコア数に合わせて数値 `5` を調節します。

## sbc6800 利用のヒント

* メモリマップは `src/sbc6800/sbc6800.cpp` の `sbc6800_state::m68_mem()` で定義されます。
* ROM の内容は `sbc6800_state::machine_reset()` 内の `memcpy()` 行で読み込まれます。
* ROM データは `src/sbc6800/sbc6800.h` で定義されています。内容は Mikbug とリセットベクタです。

## 作業環境

* Ubuntu 24.04LTS 

## 作業用リポジトリのフォーク

@tendai22 様の v0.992 (2024/12/5 版) からフォークしました。

https://github.com/ryu10/mame-sbc

## 作業ブランチ: sbc6800

https://github.com/ryu10/mame-sbc/tree/sbc6800

makefile の `TARGET=sbc6800` 行が有効になっています。

### ソースコード変更点

* `src/emuz80` をひな形に
* `src/sbc6800` 以下にマシンを記述
    * 起動時に RESET ピン操作が必要
* `src/devices/cpu/m6800` 以下を本家 mame から復元
    * 本家 mame のコミット [4358422](https://github.com/mamedev/mame/tree/4358422) を使用すること (mame-sbc のベースになるコミットに十分近いと推測される)
* `scripts` 以下の lua ビルドスクリプトを編集
* その他

## 作業ブランチ: sbc6809

https://github.com/ryu10/mame-sbc/tree/sbc6809

makefile の `TARGET=sbc6809` 行が有効になっています。

### ソースコード変更点

* sbc6800 と同じ要領で記述
    * RESET ピン操作しなくても起動する

詳細は下記の差分リンクをご覧ください。

https://github.com/tendai22/mame-sbc/compare/v0.992...ryu10:mame-sbc:sbc68-sync

## PR 用ブランチ: sbc68-sync

https://github.com/ryu10/mame-sbc/tree/sbc68-sync

* sbc6800 と sbc6809 を含むブランチです。
* このファイル `LOG-sbc68.md` を追加しました。

