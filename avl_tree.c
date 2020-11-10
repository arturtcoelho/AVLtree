#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "tree_operators.h"

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
int initialize_avl(avl_t *t){
    t->root = NULL;
    t->height = 0;
    if (DEV) {
        fprintf(stderr, "Árvore inicializada\n");
        fprintf(stderr, "root: %p\n", t->root);
        fprintf(stderr, "height: %d\n", t->height);
    }
    return 1;
}

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int insert_key_avl(avl_t *t, key_t key){

    if (tree_is_empty(t)){
        if (DEV) {
            fprintf(stderr, "Árvore vazia\n");
            fprintf(stderr, "Inserindo em %p\n", &(t->root));
        }
        insert_key(&(t->root), NULL, key);
        return 1;
    }
    
    if (t->root->key > key){
        return insert_key_by_node(t->root->left, t->root, key);
    } else {
        return insert_key_by_node(t->root->right, t->root, key);
    }
}

// procura uma chave na árvore e retorna seu valor em key, retorna 0 em caso de erro e !0 caso contrário
int search_key_avl(avl_t *t, key_t *key){
    if (!tree_is_empty(t)){
        return 0;
    }
    return 1;
}

// imprime a árvore na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int print_tree_avl(avl_t *t){
    if (!tree_is_empty(t)){
        return 0;
    }
    return 1;
}

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_avl(avl_t *t, key_t key){
    if (!tree_is_empty(t)){
        return 0;
    }

    return 1;
}

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_avl(avl_t *t){
    if (!tree_is_empty(t)){
        free(t);
        return 1;
    }
    return 1;
}