#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    // for (int i = 0; i < 10; i++){
    //     for (int j = 0; j < 10; j++){
    //         initialize_avl(&tree);
    //         for (int k = 0; k < j; k++){
    //             insert_key_avl(&tree, rand() % (i+1) + 1);
    //         }

    //         for (int k = 0; k < i; k+=(j+1)){
    //             (remove_key_avl(&tree, k));
    //         }
    //         print_parethesis(&tree);
    //         destroy_tree_avl(&tree);
    //     }
    // }

    initialize_avl(&tree);

    insert_key_avl(&tree, 4);
    insert_key_avl(&tree, 20);
    insert_key_avl(&tree, 11);
    insert_key_avl(&tree, 2);
    insert_key_avl(&tree, 25);
    insert_key_avl(&tree, 5);
    insert_key_avl(&tree, 10);
    insert_key_avl(&tree, 1);
    insert_key_avl(&tree, 15);

    // for (int i = 0; i < 200; i++){
    //     insert_key_avl(&tree, i);
    // }
    
    printf("%d\n", tree_size(&tree));
    print_tree_avl(&tree);
    print_parethesis(&tree);
    printf("altura %d\n", tree_height(&tree));
    char str[10000];
    int tam = string_parenthesis(&tree, str, 10000);
    printf("%s\n", str);
    printf("%d == %ld\n", tam, strlen(str));    

    destroy_tree_avl(&tree);

    return 0;
}
