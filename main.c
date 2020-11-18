#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "avl_module.h"

// por enquanto contém código em C para testes, 
int main(){

    srand(time(0));
    avl_t tree;

    // for (int i = 0; i < 10; i++){
    //     for (int j = 0; j < 10; j++){
    //         _initialize_avl(&tree);
    //         for (int k = 0; k < j; k++){
    //             _insert_key_avl(&tree, rand() % (i+1) + 1);
    //         }

    //         for (int k = 0; k < i; k+=(j+1)){
    //             (_remove_key_avl(&tree, k));
    //         }
    //         _print_parethesis(&tree);
    //         _destroy_tree_avl(&tree);
    //     }
    // }

    _initialize_avl(&tree);

    _insert_key_avl(&tree, 4);
    _insert_key_avl(&tree, 20);
    _insert_key_avl(&tree, 11);
    _insert_key_avl(&tree, 2);
    _insert_key_avl(&tree, 25);
    _insert_key_avl(&tree, 5);
    _insert_key_avl(&tree, 10);
    _insert_key_avl(&tree, 1);
    _insert_key_avl(&tree, 15);

    // for (int i = 0; i < 200; i++){
    //     _insert_key_avl(&tree, i);
    // }
    
    printf("%d\n", _tree_size(&tree));
    _print_tree_avl(&tree);
    _print_parethesis(&tree);
    printf("altura %d\n", _tree_height(&tree));
    char str[10000];
    int tam = _string_parenthesis(&tree, str, 10000);
    printf("%s\n", str);
    printf("%d == %ld\n", tam, strlen(str));    

    _destroy_tree_avl(&tree);

    return 0;
}
