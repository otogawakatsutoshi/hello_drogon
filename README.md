# hello_drogon

ldd で依存しているライブラリを調べる。

[drogon](https://drogon.docsforge.com/master/getting-started/)

```bash
ldd ./hello_drogon | awk '{print $3}' | sort

```