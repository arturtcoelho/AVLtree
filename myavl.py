#!/usr/bin/env python3

from avl_bridge import avl_tree
tree = avl_tree()

def process_input(s):
    if (len(s) < 2):
        return 0

    command, argument = s.split()
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
        command = input()
        while (command): # command nao eh vazio
            if (not process_input(command)):
                print("Input inválido!")
            command = input()
    except EOFError:
        pass

    tree.print_tree_parenthesis()
