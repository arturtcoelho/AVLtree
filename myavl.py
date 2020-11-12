#!/usr/bin/env python3

# declara o objeto libc, para podermos utilizar diretamente funções padrões de C
import ctypes
libc = ctypes.CDLL("/lib/x86_64-linux-gnu/libc.so.6")
avl = ctypes.CDLL("./avl_module.so")

avl.avl_teste()
print(avl.avl_teste())

# libc.printf(b"Usando printf()\n")
# libc.printf(b"Usando printf: time %ld\n", ctypes.cdll.LoadLibrary("libc.so.6").time(0))
# print("time", ctypes.cdll.LoadLibrary("libc.so.6").time(0))