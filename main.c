#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    for (int i = 0; i < 1000; i++){
        initialize_avl(&tree);

        for (int j = 0; j < 500; j++){
            int r = rand() % 500;
            insert_key_avl(&tree, r);
            // printf("Inseriu: %d  ", r);
        }

        // printf("Árvore final\n");
        // print_tree_avl(&tree);

        for (int j = 0; j < 250; j+=5){
            if (remove_key_avl(&tree, j)) {
                // printf("Removeu: %d  ", j);
                // print_tree_avl(&tree);
            }
        }
        
        // printf("Árvore final\n");
        // print_tree_avl(&tree);

        destroy_tree_avl(&tree);
    }

    // initialize_avl(&tree);

    // insert_key_avl(&tree, 30);
    // insert_key_avl(&tree, 139);
    // insert_key_avl(&tree, 334);
    // insert_key_avl(&tree, 448);
    // insert_key_avl(&tree, 286);
    // insert_key_avl(&tree, 151);
    // insert_key_avl(&tree, 105);
    // insert_key_avl(&tree, 318);
    // insert_key_avl(&tree, 0);
    // insert_key_avl(&tree, 462);

    // remove_key_avl(&tree, 0);
    // remove_key_avl(&tree, 30);
    // remove_key_avl(&tree, 105);

    // destroy_tree_avl(&tree);

    return 0;
}
