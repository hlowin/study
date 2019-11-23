# Jetson NANOへのリモート接続

## 動作環境

- ホストPC
  - ASUS UX450FDX
  - Windows10 Home
    - Tera Term 4.104
  - Ubuntu 18.04 LTS
    - Linux Kernel 4.15.0-66-generic

- Jetson NANO
  - JetPack 4.2.1
    - Ubuntu 18.04 LTS
    - Linux Kernal 4.9.140-tegra
    - CUDA toolkit 10
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB


## リモート接続手順

下記を参考に作業。

- [Jetson Nanoにリモートデスクトップ(VNC)環境を用意する](https://qiita.com/iwatake2222/items/a3bd8d0527dec431ef0f)
- [Jetson NanoでHeadlessセットアップを行う](https://qiita.com/rhene/items/fa311ca19b06605a25eb)
- [OSイメージのmicroSDカードへの書き込み](https://dev.classmethod.jp/hardware/nvidia-jetson-nano-setup/)
- [Jetson nanoにVSCode+Pythonの開発環境を整えリモートアクセスする](https://qiita.com/koppe/items/64d155bc7814441920f9)


- 同一ネットワーク上のホストPCからのアクセスは下記コマンドにて可能。

  ```bash
  ssh <ユーザー名>@<マシン名>.local
  ```

  - proxy環境下だとこの限りではなさそう。

Jetson上で下記コマンドを実行したところVNC接続できることを確認。

  ```bash
  $ sudo vncserver
  ```

色々やっていたらX-Windowのログインループにはまってしまったので、一旦クリーンインストールした後に"(方法2) Desktop Sharing(Vino)を使う"の方向で試してみる。

最終的には[Getting Started with the NVIDIA Jetson Nano Developer Kit](https://www.hackster.io/news/getting-started-with-the-nvidia-jetson-nano-developer-kit-43aa7c298797)の手順でうまくいったが、動作が重たい。


調べてみた結果、2種類の方法あり。

どちらもJetson NANOをサーバーとして、ホストPC(Windows10 or Ubuntu)をクライアントとして使用する方法。

### 1)XRDPを使用する場合

- メリット
  - Vinoと比較しておそらく軽い(だいぶ軽いはず)
  - Windows備え付けのリモートデスクトップアプリから接続可能
  - Ubuntu備え付けのリモートデスクトップアプリ(remmina)から接続可能
- デメリット
  - 別のLinuxディストリビューションで採用されているデスクトップ環境を使用するためアイコンやUI等が若干異なる
  - Terminalが使用できない
    - XTermは使用できるためそちらで代用する

1. XRDPのインストール

  ```bash
  $ sudo apt update
  $ sudo apt install xrdp
  ```

  - この時点で実はリモート接続できた…

2. Xfceのインストール

  ```bash
  $ sudo apt install xfce4
  $ cd ~/
  $ echo xfce4-session > ~/.xsession
  ```

  - xfce4から戻す場合

    - `.xsession`を開く

      ```bash
      $ ~/.xsession
      ```

    - 下記を削除

      ```
      xfce4-session
      ```

    - XRDPを再インストール

      ```bash
      $ sudo apt remove --purge xrdp
      $ sudo apt install xrdp
      ```

    - (正直戻す方法がわからない…XRDPはUnity未対応らしいがなぜできた…)

    - .xsessionrcの設定

      ```
      #!/bin/bash
  
      # Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
      #
      # Redistribution and use in source and binary forms, with or without
      # modification, are permitted provided that the following conditions
      # are met:
      #  * Redistributions of source code must retain the above copyright
      #    notice, this list of conditions and the following disclaimer.
      #  * Redistributions in binary form must reproduce the above copyright
      #    notice, this list of conditions and the following disclaimer in the
      #    documentation and/or other materials provided with the distribution.
      #  * Neither the name of NVIDIA CORPORATION nor the names of its
      #    contributors may be used to endorse or promote products derived
      #    from this software without specific prior written permission.
      #
      # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
      # EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
      # IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
      # PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
      # CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
      # EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
      # PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
      # PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
      # OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
      # (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
      # OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

      logo_path="/usr/share/backgrounds/NVIDIA_Login_Logo.png"
      # Set NVIDIA Logo after user login to desktop
      if [ -x "/usr/bin/xsetbg" ] && [ -r "${logo_path}" ]; then
              xsetbg -center "${logo_path}" -border black
      fi
      ```

3. XRDPの設定ファイルを修正

  ```bash
  $ sudo vim /etc/xrdp/startwm.sh
  ```

  - 下記通りに修正。
    - 修正しなくてもよいかも。

    ```sh
    # test -x /etc/X11/Xsession && exec /etc/X11/Xsession
    # exec /bin/sh /etc/X11/Xsession
    startxfce4
    ```

4. サービスをリスタート

  ```bash
  $ sudo systemctl enable xrdp
  $ sudo service xrdp restart
  ```

- ホストPC(Ubuntu)からの接続方法

  - `remmina`を起動

    ```
    $ remina
    ```
  
  - サーバへJetsonのIPアドレスを入力
    - Proxy環境下ではなければ、`<ホスト名>.local`で名前解決可能らしい
      - ssh等も同様

  - 色数(Depth?)は`True Color(32bit)`辺りに設定

  - 接続
    - `Session`を`Xorg`へ
    - `username`へJetsonのユーザ名を
    - `password`へJetsonのパスワードを
      - 上記を設定して`OK`

- ホストPC(Windows10)からの接続方法

  - リモートデスクトップを起動

  - サーバへJetsonのIPアドレスを入力
  
  - 接続
    - `Session`を`Xorg`へ
    - `username`へJetsonのユーザ名を
    - `password`へJetsonのパスワードを
      - 上記を設定して`OK`


### 2)VNC(Vino)を使用する場合

- メリット
  - Jetson側のデスクトップ環境をそのまま見ることができる(UIがオリジナルのものから変化しない)
  - Ubuntu備え付けのリモートデスクトップアプリ(remmina)から接続可能
- デメリット
  - かなり重い
  - Windowsより接続しようとするとVNCクライアントアプリが必要

デバッグやデモ等で動作させる際は、おそらく`1)XRDPを使用する場合`の方法がまだ使用できそうな印象

下記ご参考程度にセットアップ手順

[Getting Started with the NVIDIA Jetson Nano Developer Kit](https://www.hackster.io/news/getting-started-with-the-nvidia-jetson-nano-developer-kit-43aa7c298797)記載の方法で可能。

- `Vino`の設定ファイルを編集する
  
  ```bash
  $ sudo vim /usr/share/glib-2.0/schemas/org.gnome.Vino.gschema.xml
  ```

  下記を追記

  <key name='enabled' type='b'>
    <summary>Enable remote access to the desktop</summary>
      <description>
        If true, allows remote access to the desktop via the RFB
        protocol. Users on remote machines may then connect to the
        desktop using a VNC viewer.
      </description>
    <default>false</default>
  </key>

- コンパイルコマンドを実行

  ```bash
  $ sudo glib-compile-schemas /usr/share/glib-2.0/schemas
  ```

- `Vino`の設定

  ```bash
  $ gsettings set org.gnome.Vino require-encryption false
  $ gsettings set org.gnome.Vino prompt-enabled false
  ```

- `Desktop Shareing`の許可

  - `Application`(スタート相当のところ)から、`Desktop Sharing`を検索

  - `Allow other users to view your desktop`、`Allow other users to control your desktop`へチェック

  - `Require the user to enter the password:`へ任意のパスワードを記入

  - `Only when someone is connected`へチェック

- スタートアップアプリケーションとして設定

  - `Application`(スタート相当のところ)から、`Startup Applications`を検索

  - `Startup Applications Preferences`ウィンドウより、`Add`を選択

  - 下記様に設定して`Save`  
  
    - `Name`を`Vino`等

    - `Command`を`/usr/lib/vino/vino-server`

    - `Comment`を`VNC Server`等
  
