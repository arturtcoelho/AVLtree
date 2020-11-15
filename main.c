#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    /*for (int i = 0; i < 1; i++){
        initialize_avl(&tree);

        for (int j = 0; j < 10; j++){
            int r = rand() % 500;
            insert_key_avl(&tree, r);
            printf("Inseriu: %d  ", r);
        }

        print_tree_avl(&tree);
        printf("/n");

        for (int j = 0; j < 250; j+=5){
            if (remove_key_avl(&tree, j)) {
                printf("Removeu: %d  ", j);
                print_tree_avl(&tree);
            }
        }


        destroy_tree_avl(&tree);
    } */

    initialize_avl(&tree);
    insert_key_avl(&tree, 492);
    insert_key_avl(&tree, 123);
    insert_key_avl(&tree, 1);
    insert_key_avl(&tree, 365);
    insert_key_avl(&tree, 327);
    insert_key_avl(&tree, 282);
    insert_key_avl(&tree, 223);
    insert_key_avl(&tree, 125);
    insert_key_avl(&tree, 215);

    remove_key_avl(&tree, 125);
    remove_key_avl(&tree, 215);

    print_tree_avl(&tree);

    remove_key_avl(&tree, 365);

    destroy_tree_avl(&tree);

    return 0;
}
