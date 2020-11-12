#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    avl_t tree;
    initialize_avl(&tree);

    insert_key_avl(&tree, 1);
    insert_key_avl(&tree, 2);
    insert_key_avl(&tree, 3);
    print_tree_avl(&tree);
    remove_key_avl(&tree, 2);
    print_tree_avl(&tree);
    remove_key_avl(&tree, 3);
    print_tree_avl(&tree);
    destroy_tree_avl(&tree);

    return 0;
}
