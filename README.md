# hello_drogon

ldd で依存しているライブラリを調べる。

```bash
ldd ./hello_drogon | awk '{print $3}' | sort

```