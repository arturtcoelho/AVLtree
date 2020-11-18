#!/usr/bin/env python3
from avl_bridge import avl_tree
import random

tree = avl_tree()

#for i in range(10):
#    for j in range(10):
#        tree = avl_tree()
#        for k in range(j):
#            tree.insert_key(random.randrange(1, i+2))
#        }
#        for k in range(i, step=j+1):
#            tree.remove_key(k)
#        }
#        print(tree)
#        tree.destroy()
#    }
#}

for i in range(1000):
    tree.insert_key(i)

#for i in range(200)
#    tree.insert_key(i)

# print(len(tree))

tree.print_tree()
tree.print_tree_parenthesis()
str = tree.as_parenthesis_string()
print(str)

# printf("altura %d\n", _tree_height(&tree))

tree.destroy()
