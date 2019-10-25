# Jetson NANOのセットアップ/諸々の環境構築

## 動作環境

- ホストPC
  - ASUS UX450FDX
  - Windows10 Home
  - Tera Term 4.104

- Jetson NANO
  - JetPack 4.2.1
    - Ubuntu 18.04 LTS
    - CUDA toolkit 10
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB


## セットアップ

[Jetson nano セットアップ方法まとめ](https://qiita.com/M_Hiro/items/3fb1f17c43a32162a8f3)を参考にセットアップ。

- 使用するツール
  - [SD Memory Card Formatter](https://www.sdcard.org/downloads/formatter/eula_windows/)
  - [balenaEtcher](https://www.balena.io/etcher/)

- OSイメージ(JetPack)
  - [Jetson Download Center](https://developer.nvidia.com/embedded/downloads)

- JetCard
  - [jetcard](https://github.com/NVIDIA-AI-IOT/jetcard)
  - このイメージを使用してしまえば、諸々の設定をせずに済む模様。


## リモート接続

下記を参考に作業。

- [Jetson Nanoにリモートデスクトップ(VNC)環境を用意する](https://qiita.com/iwatake2222/items/a3bd8d0527dec431ef0f)
- [Jetson NanoでHeadlessセットアップを行う](https://qiita.com/rhene/items/fa311ca19b06605a25eb)
- [OSイメージのmicroSDカードへの書き込み](https://dev.classmethod.jp/hardware/nvidia-jetson-nano-setup/)



