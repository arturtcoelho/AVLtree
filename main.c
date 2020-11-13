#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;
    initialize_avl(&tree);

    for (int i = 0; i < 20; i++){
        int r = rand() % 30;
        printf("inserindo %d ", r);
        insert_key_avl(&tree, r);
        print_tree_avl(&tree);
    }
    printf("Arvore total \n");
    print_tree_avl(&tree);

    for (int i = 0; i < 20; i++){
        printf("removendo %d ", i);
        remove_key_avl(&tree, i);
        print_tree_avl(&tree);
    }
    printf("arvore final\n");
    print_tree_avl(&tree);

    destroy_tree_avl(&tree);

    return 0;
}
