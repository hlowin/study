# Jetson NANO上でのカーネルリビルド

## 動作環境

- ホストPC
  - ASUS UX450FDX
  - Windows10 Home
    - Tera Term 4.104
  - Ubuntu 18.04 LTS Linux Kernel 4.15.0 amd64

- Jetson NANO
  - JetPack 4.2.1
    - Ubuntu 18.04 LTS
    - CUDA toolkit 10
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB

## 手順

下記に示す2通りの方法を試す。

1. [Ubuntu 16.04でカーネルを再ビルドする](https://www.hiroom2.com/2016/05/18/ubuntu-16-04%E3%81%A7%E3%82%AB%E3%83%BC%E3%83%8D%E3%83%AB%E3%82%92%E5%86%8D%E3%83%93%E3%83%AB%E3%83%89%E3%81%99%E3%82%8B/)を参考に作業。
  - "make -j4 Image"実行時にビルドエラーが発生。

2. [Jetson Nanoのカーネル再コンパイル](https://qiita.com/yamamo-to/items/6fc622df7b5cce3eccfb)の手順でカーネルのマイナーバージョンのみを書き換えてビルドしようとしたが、ビルドエラーが発生。

上記2通りの方法以外のアプローチを考える。

カーネルのクリーンなソースコードをダウンロードし、元々の設定を反映した後にビルドする手順でやってみる。

1. linux kernel 4.15.xのソースコードをダウンロード。

  ```bash
  $ wget https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.15.1.tar.gz
  ```

2. 現在のconfigファイルを反映。

  ```bash
  $ zcat /proc/config.gz  > .config
  ```

3. ビルド。

  ```bash
  $ make oldconfig
  ($ make O=/usr/src/linux-headers-4.x.x-xxxx oldconfig)
  $ make prepare
  $ make modules_prepare
  $ make -j4 Image
  $ make -j4 modules
  ```

4. インストール。

  ```bash
  $ sudo make modules_install
  $ sudo cp -p /boot/Image /boot/Image.org
  $ sudo cp arch/arm64/boot/Image /boot/Image
  ```

5. 再起動。

  ```bash
  $ sudo reboot
  ```

ビルド&インストールはできたが、再起動したところOS起動せず。
