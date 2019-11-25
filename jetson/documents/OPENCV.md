# Jetson NANOのイメージバックアップ(.img化)

## 動作環境

- ホストPC
  - ASUS UX450FDX
  - Ubuntu 18.04 LTS

- Jetson NANO
  - JetPack 4.2.1
    - Ubuntu 18.04 LTS
    - CUDA toolkit 10
    - OpenCV 4.1.1
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB

## 参考

[Jetson Nano へ OpenCV 4.1.0 をインストールする](https://qiita.com/asahi0301/items/3c287190348552f19415)
[Jetson Nano に OpenCV 4.1.1 をインストールする](https://qiita.com/daisuzu_/items/f17d365a895a599f832f)

## 手順

1. インストールスクリプトをクローン

  ```bash
  $ git clone https://github.com/AastaNV/JEP
  ```

2. インストールスクリプトの実行

  ```bash
  $ cd JEP/script
  $ sh install_opencv4.1.1_Jetson.sh opencv
  ```

3. python3からの実行確認、バージョン確認

  ```bash
  $ python3
  >>> import cv2
  >>> cv2.__version__
  '4.1.1'
  ```