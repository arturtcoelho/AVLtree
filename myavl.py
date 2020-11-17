#!/usr/bin/env python3

from avl_bridge import avl_tree
tree = avl_tree()

def input_exists(s):
    return len(s) > 0

def input_format(s):
    if (len(s) < 2):
        return 0

    sl = slice(2)
    comm = s[sl]
    if (comm != "i " and comm != "r "):
        return 0

    sl = slice(2, len(s))
    try:
        n = int(s[sl])
    except ValueError:
        return 0

    if (comm == "i "): # input na árvore 
        tree.insert_key(n)
    else: # remove da árvore
        tree.remove_key(n)

    return 1

if __name__ == '__main__':
    try:
        comm = input()
        while (input_exists(comm)):
            if (not input_format(comm)):
                print("erro de input")
            comm = input()
    except EOFError:
        pass

    tree.print_tree_parenthesis()
