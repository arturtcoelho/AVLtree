#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;
    initialize_avl(&tree);

    // insert_key_avl(&tree, 10);
    // insert_key_avl(&tree, 5);
    // insert_key_avl(&tree, 15);
    // insert_key_avl(&tree, 20);
    // insert_key_avl(&tree, 1);
    // insert_key_avl(&tree, 12);
    // insert_key_avl(&tree, 7);
    // insert_key_avl(&tree, 25);
    // insert_key_avl(&tree, 30);
    // insert_key_avl(&tree, 35);
    // insert_key_avl(&tree, 40);
    // insert_key_avl(&tree, 17);
    // print_tree_avl(&tree);
    // remove_key_avl(&tree, 15);
    // print_tree_avl(&tree);

    for (int i = 0; i < 20; i++){
        int r = rand() % 100;
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
