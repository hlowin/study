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

2. [Jetson Nanoのカーネル再コンパイル](https://qiita.com/yamamo-to/items/6fc622df7b5cce3eccfb)の手順でカーネルのマイナーバージョンのみを書き換えてビルドしようとしたが、ビルドエラーが発生。
