#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface para python esse será um arquivo python
int main(){

    avl_t tree;
    initialize_avl(&tree);

    for (int i = 0; i < 20; i++){
        insert_key_avl(&tree, i * (i % 2 ? -1 : 1));
    }

    printf("Print 1st tree\n");
    print_tree_avl(&tree);
    destroy_tree_avl(&tree);
    printf("Print 2nd tree\n");
    print_tree_avl(&tree);
    
    return 0;
}
