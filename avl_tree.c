#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "tree_operators.h"

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 ao contrário
int initialize_avl(avl_t *t){
    t->root = NULL;
    t->height = -1;
    return 1;
}

// adiciona uma chave key_t na árvore, retorna 0 em caso de erro e !0 ao contrário
int add_key_avl(avl_t *t, key_t key){
    node_t *rt = t->root;

    if (!tree_initialized(t)){
        initialize_avl(t);
        rt = (node_t*)malloc(sizeof(node_t));
        rt->key = key;
        rt->top = NULL;
        rt->left = NULL;
        rt->right = NULL;
        return 1;
    }

    if (rt->key > key){
        return add_key_by_node(rt->left, rt, key);
    } else {
        return add_key_by_node(rt->right, rt, key);
    }
}

// procura uma chave na árvore e insere seu valor em key, retorna 0 em caso de erro e !0 ao contrário
int find_key_avl(avl_t *t, key_t *key){
    if (!tree_initialized(t)){
        return 0;
    }
    return 1;
}

// imprime a árvore na saída padrão, retorna 0 em caso de erro e !0 ao contrário
int print_tree_avl(avl_t *t){
    if (!tree_initialized(t)){
        return 0;
    }
    return 1;
}

// remove uma chave da árvore, retorna 0 em caso de erro e !0 ao contrário
int delete_key_avl(avl_t *t, key_t key){
    if (!tree_initialized(t)){
        return 0;
    }

    return 1;
}

// destroi a árvore, retorna 0 em caso de erro e !0 ao contrário
int remove_tree_avl(avl_t *t){
    if (!tree_initialized(t)){
        free(t);
        return 1;
    }
    return 1;
}