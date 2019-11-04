# VIMの基本設定

xxxx.jsonや~/.bashrc系のテキストファイル、Makefileを編集する際に少しvimでいじることも多いので、デフォルトの設定について残しておく。

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

## 基本設定

1. .vimrcを作成。

  ```bash
  $ vim ~/.vimrc
  ```

2. 下記を追記。

```vimrc
" Display Line number
set number

" If search in Lower Case then ignore Upper/Lower case
set smartcase

" If error occured then not call beep bells
set noerrorbells

" Display correspoinding Brackets and Braces
set showmatch matchtime=1

" Smart indent
set smartindent

" If input TAB Key then insert space instead of TAB
set expandtab
set tabstop=2
set shiftwidth=2
```