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


## Visual Studio Code導入

[Jetson nanoにVS Codeをコンパイルしてインストールする](https://kokensha.xyz/jetson/compile-and-install-vs-code-to-jetson-nano/)を参考にインストールしてみる。

途中でnvmが見つからないとのエラーが出力。

```bash
bash: nvm: command not found
```

下記コマンドでPATH設定を即時反映させる。

```bash
$ source ~/.bashrc
```

yarn実行時に下記エラーが発生。

```bash
error /home/hiroaki/work/git/library/vscode/remote/node_modules/node-pty: Command failed.
error /home/hiroaki/work/git/library/vscode/remote/node_modules/nsfw: Command failed.
error /home/hiroaki/work/git/library/vscode/remote/node_modules/spdlog: Command failed.
error /home/hiroaki/work/git/library/vscode/remote/node_modules/native-watchdog: Command failed.
```

"node-pty"をインストール。

```bash
$ sudo apt-get install npm
$ npm install node-pty
$ npm install nsfw
$ npm install spdlog
$ npm install native-watchdog
```

そもそもnpmのバージョンが古いことに起因するエラーではないかと考え、最新版をインストール。

```bash
$ sudo npm install npm@latest -g
```

コマンドを実行した後もnpmのバージョンは3.5.2から変わらなかったため、意味無し？

結局、nsfwのエラーが出力されてしまう。

```bash
$ sudo npm install -g node-gyp
```

[Quick build guide for visual studio code on the nano](https://devtalk.nvidia.com/default/topic/1049448/jetson-nano/quick-build-guide-for-visual-studio-code-on-the-nano/1)の方法を試してみる。


下記コマンドを実行したところ、ビルドが通った模様。

```bash
$ curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
$ sudo apt-get install -y nodejs
```

拡張機能を使用するための作業。

```bash
$ sudo vim /usr/share/code-oss/resources/app/product.json
```

下記を追記。

```
  "extensionsGallery": {
 		"serviceUrl": "https://marketplace.visualstudio.com/_apis/public/gallery",
  		"cacheUrl": "https://vscode.blob.core.windows.net/gallery/index",
  		"itemUrl": "https://marketplace.visualstudio.com/items"
	}
```
