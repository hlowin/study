# Jetson NANOへのリモート接続

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


## リモート接続手順

下記を参考に作業。

- [Jetson Nanoにリモートデスクトップ(VNC)環境を用意する](https://qiita.com/iwatake2222/items/a3bd8d0527dec431ef0f)
- [Jetson NanoでHeadlessセットアップを行う](https://qiita.com/rhene/items/fa311ca19b06605a25eb)
- [OSイメージのmicroSDカードへの書き込み](https://dev.classmethod.jp/hardware/nvidia-jetson-nano-setup/)
- [Jetson nanoにVSCode+Pythonの開発環境を整えリモートアクセスする](https://qiita.com/koppe/items/64d155bc7814441920f9)

同一ネットワーク上のホストPCからのアクセスは下記コマンドにて可能。

```bash
ssh <ユーザー名>@<マシン名>.local
```

Jetson上で下記コマンドを実行したところVNC接続できることを確認。

```bash
$ sudo vncserver
```

色々やっていたらX-Windowのログインループにはまってしまったので、一旦クリーンインストールした後に"(方法2) Desktop Sharing(Vino)を使う"の方向で試してみる。

最終的には[Getting Started with the NVIDIA Jetson Nano Developer Kit](https://www.hackster.io/news/getting-started-with-the-nvidia-jetson-nano-developer-kit-43aa7c298797)の手順でうまくいったが、動作が重たい。
