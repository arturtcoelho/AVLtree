#!/usr/bin/env python3
"""
Modulo ponte entre scripts Python e a biblioteca avl_tree.so
Autores: Gabriel Nascarella Hishida e Artur Temporal Coelho
"""

import ctypes
from ctypes import byref
# Usamos 'byref' muitas vezes

buffer_size = 16

# Importando a lib para usos futuros:
lib = ctypes.CDLL("./avl_module.so")

class node(ctypes.Structure):
    """Nodo definido pela struct node_t""" 

    pass
    # ctypes incompletos;
    # Precisamos que o nodo seja conhecido pelo parser
    # antes de declararmos ponteiros para o mesmo
    # Verifique docs/sources.txt: Tipos Incompletos

# Suas definicoes sao feitas apos sua declaracao:

node._fields_ = [
    ("key", ctypes.c_int),
	("top", ctypes.POINTER(node)),
	("left", ctypes.POINTER(node)),
	("right", ctypes.POINTER(node)),
]

def _node_repr_(self):
    return int(self.key)

node.__repr__ = _node_repr_
# Fim da definicao de 'node'

class avl_tree(ctypes.Structure):
    """Arvore AVL, definida a partir da struct avl_t"""

    _fields_ = [
        ("root", ctypes.POINTER(node)),
    ]

    def __init__(self):
        """Inicializa a classe/struct"""
        # Verifique docs/sources.txt: By Reference
        lib.initialize_avl(byref(self))

    def insert_key(self, key):
        """
        Insere uma chave int na árvore,
        retorna 0 em caso de erro e !0 caso contrário
        """
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.insert_key_avl(byref(self), c_key)

    def search_key(self, key):
        """
        Procura uma chave key na árvore,
        retorna 0 em caso de erro e !0 caso contrário
        """
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.search_key_avl(byref(self), c_key)

    def remove_key(self, key):
        """
        Remove uma chave da árvore,
        retorna 0 em caso de erro e !0 caso contrário
        """
        if type(key) != int:
            raise TypeError
        c_key = ctypes.c_int(key)

        return lib.remove_key_avl(byref(self), c_key)

    def print_tree(self):
        """
        Imprime a árvore in-order na saída padrão,
        retorna 0 em caso de erro e !0 caso contrário
        """
        return lib.print_tree_avl(byref(self))

    def print_tree_parenthesis(self):
        """Imprime a árvore com a notação de parenteses"""
        return lib.print_parethesis(byref(self))

    def as_string(self):
	"""Retorna o texto de 'print_tree_parenthesis' como string"""
        size = len(self) * buffer_size
        string = ctypes.create_string_buffer(size)
        lib.string_parenthesis(byref(self), byref(string), size)
        ctypes.cast(string, ctypes.c_char_p)
        s = str(string.value)
#         sl = slice(2, len(s)-1)
#         s = s[sl]
        return s[2:-1]

    def size(self):
	"""Retorna o tamanho da árvore"""
        return lib.tree_size(byref(self))

    def destroy(self):
        """Destroi a árvore, retorna 0 em caso de erro e !0 caso contrário"""
        return lib.destroy_tree_avl(byref(self))

    def __del__(self):
        """Destrutor de classe"""
        return self.destroy()

    def __str__(self):
	"""Verificador usado pela funcao built-in 'print'"""
        return self.as_string()

    def __contains__(self, key):
        """ Verificador usado pelo operador 'in' """
        # Mais em docs/source.txt: In Operator 
        return self.search_key(key)

    def __repr__(self):
        return '({})'.format(self.root)

    def __len__(self):
	"""Verificador usado pela funcao built-in 'len()'"""
        return self.size()
