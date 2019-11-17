# Jetson NANOへJetbot Library(?)導入

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
    - Python 2.7.15+
    - Python 3.6.8
  - SANDISK microSD CLASS 10 UHS-1 U3 64GB

## 手順

1. [jetbot](https://github.com/NVIDIA-AI-IOT/jetbot)をクローン。

  ```bash
  $ git clone https://github.com/NVIDIA-AI-IOT/jetbot.git
  ```

2. Jupytor Notebookを導入。

  ```bash
  $ sudo apt install nodejs npm
  $ sudo apt install python3-pip
  $ sudo pip3 install ipython[all]
  $ sudo pip3 install jupyter jupyterlab
  $ sudo jupyter labextension install @jupyter-widgets/jupyterlab-manager
  $ jupyter lab --generate-config
  ```
3. Jupytor Notebookを起動。

  ```bash
  $ jupytor notebook
  ```

...

## 上記のようなややこしい手順を踏んでいますが...

もしかしたら、下記手順で大丈夫かもしれない。

0. OSイメージをインストール。

1. [jetcard](https://github.com/NVIDIA-AI-IOT/jetcard)記載のインストール方法を実行。

2. [jetbot](https://github.com/NVIDIA-AI-IOT/jetbot)記載のインストール方法を実行。

3. [installLibrealsense](https://github.com/jetsonhacksnano/installLibrealsense)記載のインストール方法を実行。
