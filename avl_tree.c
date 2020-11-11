#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "tree_operations.h"

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
int initialize_avl(avl_t *t){
    // inicializa os valores de root e height
    t->root = NULL;
    t->height = 0;
    if (DEV) {
        fprintf(stderr, "Árvore em %p inicializada\n", t);
    }
    return 1;
}

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int insert_key_avl(avl_t *t, key_t key){

    // caso ainda não existam nodos presentes
    if (tree_is_empty(t)){
        if (DEV) {
            fprintf(stderr, "Árvore vazia\n");
            fprintf(stderr, "Inserindo em %p\n", &(t->root));
        }
        insert_key(&(t->root), NULL, key);
        return 1;
    }
    
    // insere na sub-árvore a esquerda ou direita
    if (t->root->key > key){ // esquerda
        if (DEV) {fprintf(stderr, "Inserindo key: %d em %p\n", key, &(t->root->left));}
        return insert_key_by_node(&(t->root->left), t->root, key);
    } else { // direita
        if (DEV) {fprintf(stderr, "Inserindo key: %d em %p\n", key, &(t->root->right));}
        return insert_key_by_node(&(t->root->right), t->root, key);
    }
}

// procura uma chave na árvore, retorna 0 em caso de erro e !0 caso contrário
int search_key_avl(avl_t *t, key_t key){
    if (tree_is_empty(t)){
        if (DEV) {fprintf(stderr, "Buscando key %d numa árvore vazia\n", key);}
        return 0;
    }

    
    if (t->root->key == key) {
        if (DEV) {fprintf(stderr, "Achou key %d na root\n", key);}
        return 1;
    }

    // busca recursivamente
    if (t->root->key > key) { // esquerda
        if (DEV) {fprintf(stderr, "Buscando key %d á esquerda\n", key);}
        return search_key_by_node(t->root->left, key);
    } else { // direita
        if (DEV) {fprintf(stderr, "Buscando key %d á direita\n", key);}
        return search_key_by_node(t->root->right, key);
    }

    return 1;
}

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int print_tree_avl(avl_t *t){
    if (tree_is_empty(t)){
        return 1;
    }

    // imprime a árvore recursivamente
    print_tree_by_node(t->root);
    printf("\n");
    
    return 1;
}

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_avl(avl_t *t, key_t key){
    if (tree_is_empty(t)){
        return 0;
    }



    return 1;
}

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_avl(avl_t *t){
    if (tree_is_empty(t)){
        return 1;
    }
    return 1;
}