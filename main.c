#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface para python esse será um arquivo python
int main(){

    avl_t tree;

    printf("inicializa: %d\n", initialize_avl(&tree));
    printf("insert key: %d\n", insert_key_avl(&tree, 10));
    printf("insert key: %d\n", insert_key_avl(&tree, 5));
    printf("insert key: %d\n", insert_key_avl(&tree, 20));
    printf("key1 %d\n", tree.root->key);
    printf("key2 %d\n", tree.root->right->key);
    printf("key3 %d\n", tree.root->left->key);
    printf("key1 %d\n", search_key_avl(&tree, 10));
    printf("key3 %d\n", search_key_avl(&tree, 20));
    printf("key2 %d\n", search_key_avl(&tree, 5));
    printf("key4 %d\n", search_key_avl(&tree, 30));
    printf("insert key: %d\n", insert_key_avl(&tree, 30));
    printf("key4 %d\n", search_key_avl(&tree, 30));

    return 0;
}
