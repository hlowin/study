# Googleコーディングスタイルに準拠したコーディングのためのツール導入

## cpplint

[cpplint](https://marketplace.visualstudio.com/items?itemName=mine.cpplint)を参考に導入。

## clang_format_style

[Visual Studio Codeでの行頭カッコを何とかしたい](https://qiita.com/Hiragi-GKUTH/items/998c0276e4e62e5c1def)を参考に設定。

"settings.json"へ下記を追記。

```json
    "C_Cpp.clang_format_style": "Google",
    "editor.formatOnSave": true,
    "editor.formatOnType": true,
    "ColumnLimit": 80,
    "[cpp]": {
        "editor.tabSize": 2,
    },
```

