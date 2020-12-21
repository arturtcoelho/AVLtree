#!/usr/bin/env python3

"""
Script de interface do usuario com uma arvore AVL.
Usa o modulo python 'avl_bridge.py',
que o conecta com a biblioteca C 'avl_module.c'.

Comandos:
    'p'
        Imprime a arvore na notacao de parenteses
    'i {x}'
        Insere {x} na arvore AVL
    'r {x}'
        Remove {x} da arvore, se {x} pertence a mesma
    's {x}'
        Imprime 'True' na saida padrao se {x} pertence a arvore,
        'False' caso contrario

Apos cada comando, a arvore eh desenhada com seus grafos,
da esquerda para direita.
"""
__author__ = "Gabriel Nascarella Hishida and Artur Temporal Coelho"

from avl_bridge import avl_tree
tree = avl_tree()

def process_input(line):
    """
    Processa linha de input.
    Retorna 1 se a linha contem um comando valido (e o executa);
    Retorna 0 caso contrario
    """

    try:
        # separa a linha em comandos e argumentos
        command, arguments = line.split(maxsplit=1)
    except ValueError: # comando sem argumentos
        command = line

    # Comandos sem argumentos:
    if (command == "p"): # imprime a arvore (notacao de parenteses)
        print(tree)
        return 1

    # Comandos com argumentos:
    try:
        n = int(arguments)
    except: # Argumento invalido
        return 0

    if (command == "i"): # input na árvore 
        tree.insert_key(n)
    elif (command == "r"): # remove da árvore
        tree.remove_key(n)
    elif (command == "s"): # pesquisa na arvore
        print(n in tree)
    else: # comando nao encontrado
        return 0

    return 1


if __name__ == '__main__':
    try:
        line = input()
        while (line): # linha nao eh vazia
            if (not process_input(line)):
                print("Input inválido!")
            tree.print_graph() # descomente essa linha para ver a evolução da árvore
            line = input()

    except (EOFError, KeyboardInterrupt):
        pass

    # tree.print_graph() # descomente essa linha para ver a árvore final
    tree.print_with_height()