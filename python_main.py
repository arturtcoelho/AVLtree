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

tree.insert_key(4)
tree.insert_key(20)
tree.insert_key(11)
tree.insert_key(2)
tree.insert_key(25)
tree.insert_key(5)
tree.insert_key(10)
tree.insert_key(1)
tree.insert_key(15)

tree.remove_key(15)

# for i in range(1000):
#     tree.insert_key(i)

#for i in range(200)
#    tree.insert_key(i)

# print(len(tree))

tree.print_tree()
tree.print_tree_parenthesis()
str = tree.as_string()
print(str)

# printf("altura %d\n", _tree_height(&tree))

tree.destroy()
