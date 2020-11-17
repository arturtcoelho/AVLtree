#!/usr/bin/env python3

from avl_bridge import avl_tree
tree = avl_tree()

def process_input(s):
    if (len(s) < 2):
        return 0

    command, argument = s.split(maxsplit=1)
    if (command != "i" and command != "r"):
        return 0

    try:
        n = int(argument)
    except ValueError:
        return 0

    if (command == "i"): # input na árvore 
        tree.insert_key(n)
    else: # remove da árvore
        tree.remove_key(n)

    return 1

if __name__ == '__main__':
    try:
        line = input()
        while (line): # linha nao eh vazia
            if (not process_input(line)):
                print("Input inválido!")
            line = input()
    except EOFError:
        pass

    tree.print_tree_parenthesis()
