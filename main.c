#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    // for (int i = 0; i < 1000; i++){
    //     for (int j = 0; j < 100; j++){
    //         initialize_avl(&tree);
    //         for (int k = 0; k < j; k++){
    //             insert_key_avl(&tree, rand() % (i+1) + 1);
    //         }

    //         for (int k = 0; k < i; k+=(j+1)){
    //             (remove_key_avl(&tree, k));
    //         }
    //         // print_tree_avl(&tree);
    //         destroy_tree_avl(&tree);
    //     }
    // }

    initialize_avl(&tree);

    insert_key_avl(&tree, 5);
    insert_key_avl(&tree, 10);
    insert_key_avl(&tree, 1);
    insert_key_avl(&tree, 15);
    insert_key_avl(&tree, 4);
    insert_key_avl(&tree, 20);
    insert_key_avl(&tree, 11);
    insert_key_avl(&tree, 2);

    printf("%d\n", tree_size(&tree));
    print_tree_avl(&tree);
    print_parethesis(&tree);

    destroy_tree_avl(&tree);

    return 0;
}
