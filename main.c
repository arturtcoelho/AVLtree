#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    for (int i = 0; i < 1; i++){
        initialize_avl(&tree);

        for (int j = 0; j < 100; j++){
            int r = rand() % 500;
            insert_key_avl(&tree, r);
        }

        for (int j = 0; j < 250; j+=5){
            remove_key_avl(&tree, j);
        }

        destroy_tree_avl(&tree);
    }

    return 0;
}
