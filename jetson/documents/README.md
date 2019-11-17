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


## セットアップ手順

[Jetson nano セットアップ方法まとめ](https://qiita.com/M_Hiro/items/3fb1f17c43a32162a8f3)を参考にセットアップ。

- 使用するツール
  - [SD Memory Card Formatter](https://www.sdcard.org/downloads/formatter/eula_windows/)
  - [balenaEtcher](https://www.balena.io/etcher/)

- OSイメージ(JetPack)
  - [Jetson Download Center](https://developer.nvidia.com/embedded/downloads)

- JetCard
  - [jetcard](https://github.com/NVIDIA-AI-IOT/jetcard)
  - このイメージを使用してしまえば、諸々の設定をせずに済む模様。
