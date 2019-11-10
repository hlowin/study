# Jetson NANOのイメージバックアップ(.img化)

## 動作環境

- ホストPC
  - ASUS UX450FDX
  - Ubuntu 18.04 LTS
  - Windows10 Home
    - Tera Term 4.104

- Jetson NANO
  - JetPack 4.2.1
    - Ubuntu 18.04 LTS
    - CUDA toolkit 10
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB

## 前提条件

ホストPCはUbuntuがインストールされている状態で試行。

## 手順

[Jetson NanoのSDカードを丸ごとハードコピー（イメージ化）する方法](https://qiita.com/karaage0703/items/e2170d4d1eab7fdabe46)を参考。

重要なポイントは下記。

1. Jetson SDのパーティション変更、イメージの保存のために容量が余っているUbuntuPCを用意。

2. GPartedでパーティション編集する際は、編集するパーティションに対して必ず"Unmount"を実行。

3. SDカードのイメージ化コマンド。

  ```bash:bash
  $ sudo dd bs=4M if=/dev/sdb of=jetcard_image.img status=progress count=6250
  ```

  `bs=4M`は1度に4MB書き込むことを意味。

  `count=6250`は6250 * 4MB = 25000MB = 25GBサイズのイメージを書き込むことを意味。

  - 例

    ```bash:bash
    $ sudo dd bs=4M if=/dev/sda of=jetcard_image.img status=progress count=8000
    $ sudo dd bs=4M if=/dev/sda status=progress count=8000  | gzip -c > jetcard_image.img.gz
    ```