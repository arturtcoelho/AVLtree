#!/usr/bin/env python3

from avl_bridge import avl_tree
tree = avl_tree()

def process_input(line):

    try:
        # separa a linha em comandos e argumentos
        command, arguments = line.split(maxsplit=1)
    except ValueError:
        # comando sem argumentos
        command = line

    # Comandos sem argumentos:
    if (command == "p"): # imprime a arvore
        print(tree)
        return 1

    # Comandos com argumentos:
    try:
        n = int(arguments)
    except:
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
            line = input()
    except (EOFError, KeyboardInterrupt):
        pass

    print(tree)
    tree.print_with_height()
