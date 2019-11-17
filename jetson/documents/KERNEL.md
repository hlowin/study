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

## カーネルのクリーンなソースコードをダウンロードし、元々の設定を反映した後にビルドする手順でやってみる。

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


## "INZI"に関するパッチ当てを行う

SR300/SR305のDepth Streamを取得する際に、下記エラーが出力される。

```bash
The requested pixel format 'INZI' is not natively supported by the Linux kernel...
```

- [How to manually パッチ the kernel for INZI? #1863](https://github.com/IntelRealSense/librealsense/issues/1863)で色々議論している...

[buildJetsonTX2Kernel](https://github.com/syedharoonalam/buildJetsonTX2Kernel)
- INZIに関するパッチを当てているようだが、GCCのバージョン違いなのか最新のバージョンのカーネル上でビルドしているからなのか上手くビルドできない…

ので、上記リポジトリでのスクリプトでパッチを当てている箇所について現バージョンのカーネルソースに対してマニュアルでパッチを当てて(コーディングして)ビルドしてみる。

- 参考：[Jetson NanoでMIDIを使うためにカーネルビルド](https://qiita.com/karaage0703/items/9bef6aeec9ad24f647c6)

1. Jetpack中のカーネルソースコードを取得。

  ```bash
  $ wget https://developer.nvidia.com/embedded/dlc/l4t-sources-32-1-jetson-nano -O l4t-sources-32-1-jetson-nano.tar.gz
  ```

2. 解凍。

  ```bash
  $ tar xvf l4t-sources-32-1-jetson-nano.tar.gz
  ```

3. カーネルのソースコードを解凍。

  ```bash
  $ cd public_sources
  $ tar xvf kernel_src.tbz2
  $ cd kernel/kernel-4.9
  ```

4. コンフィグファイルの書き出し。

  ```bash
  $ zcat /proc/config.gz  > .config
  ```

5. 手動でパッチ当て。

  ```bash
  $ code-oss drivers/media/usb/uvc/uvcvideo.h
  ```

  Line:141辺りに下記を追記。

  ```h
  /* patch for INZI -sta */
  #define UVC_GUID_FORMAT_INVZ \
    { 'I',  'N',  'V',  'Z', 0x90, 0x2d, 0x58, 0x4a, \
    0x92, 0x0b, 0x77, 0x3f, 0x1f, 0x2c, 0x55, 0x6b}
  #define UVC_GUID_FORMAT_INZI \
    { 'I',  'N',  'Z',  'I', 0x66, 0x1a, 0x42, 0xa2, \
    0x90, 0x65, 0xd0, 0x18, 0x14, 0xa8, 0xef, 0x8a}
  #define UVC_GUID_FORMAT_INVI \
    { 'I',  'N',  'V',  'I', 0xdb, 0x57, 0x49, 0x5e, \
    0x8e, 0x3f, 0xf4, 0x79, 0x53, 0x2b, 0x94, 0x6f}
  /* patch for INZI -end */
  ```

  ```bash
  $ code-oss drivers/media/usb/uvc/uvc_driver.c
  ```

  "static struct uvc_format_desc uvc_fmts[]"内に下記のメンバを追記。(Line:171辺りに下記を追記。)

  ```c
	/* patch for INZI -sta */
  {
    .name		= "Depth data 16-bit (Z16)",
    .guid		= UVC_GUID_FORMAT_INVZ,
    .fcc		= V4L2_PIX_FMT_Z16,
  },
  {
    .name		= "IR:Depth 26-bit (INZI)",
    .guid		= UVC_GUID_FORMAT_INZI,
    .fcc		= V4L2_PIX_FMT_INZI,
  },
  {
    .name		= "Greyscale 10-bit (Y10 )",
    .guid		= UVC_GUID_FORMAT_INVI,
    .fcc		= V4L2_PIX_FMT_Y10,
  },
	/* patch for INZI -end */
  ```

  ```bash
  $ code-oss include/uapi/linux/videodev2.h
  ```

  Line:657辺りに下記を追記。

  ```c
  /* patch for INZI -sta */
  #define V4L2_PIX_FMT_MT21C    v4l2_fourcc('M', 'T', '2', '1') /* Mediatek compressed block mode  */
  #define V4L2_PIX_FMT_INZI     v4l2_fourcc('I', 'N', 'Z', 'I') /* Intel Infrared 10-bit linked with Depth 16-bit */
  /* patch for INZI -end */
  ```

6. カーネルビルド

  ```bash
  $ make oldconfig
  $ make prepare
  $ make modules_prepare
  $ make -j4 Image && make -j4 modules
  $ sudo make modules_install
  $ sudo cp arch/arm64/boot/Image /boot/Image
  ```