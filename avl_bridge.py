#!/usr/bin/env python3

import ctypes
from ctypes import byref
# Usamos 'byref' muitas vezes

# Importando a lib para usos futuros:
lib = ctypes.CDLL("./avl_module.so")

class node(ctypes.Structure):
    """Nodo definido pela struct node_t""" 

    pass
    # ctypes incompletos;
    # Precisamos que o nodo seja conhecido pelo parser
    # antes de declararmos ponteiros para o mesmo
    # Mais em docs/sources.txt (Tipos Incompletos)

# Suas definicoes sao feitas apos sua declaracao:

node._fields_ = [
    ("key", ctypes.c_int),
	("top", ctypes.POINTER(node)),
	("left", ctypes.POINTER(node)),
	("right", ctypes.POINTER(node)),
]


class avl_tree(ctypes.Structure):
    """Arvore AVL, definida a partir da struct avl_t"""

    _fields_ = [
        ("root", ctypes.POINTER(node)),
        ("height", ctypes.c_int)
    ]

    def __init__(self):
        # Verifique docs/sources.txt: By Reference
        lib.initialize_avl(byref(self))

    def insert_key(self, key):
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.insert_key_avl(byref(self), c_key)

    def search_key(self, key):
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.search_key_avl(byref(self), c_key)

    def remove_key(self, key):
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.remove_key_avl(byref(self), c_key)

    def __str__(self):
        return lib.print_tree_avl(byref(self))

    def __del__(self):
        return lib.destroy_key_avl(byref(self))

    def __repr__(self):
        return '({}, {})'.format(self.root, self.height)

