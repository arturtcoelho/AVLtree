#include <stdio.h>
#include <stdlib.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"
#include "print_tree.h"

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
int initialize_avl(avl_t *t){
    // inicializa o valor de root
    t->root = NULL;
    return 1;
}

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int insert_key_avl(avl_t *t, key_t key){

    // caso ainda não existam nodos presentes
    if (tree_is_empty(t)) return insert_key(&(t->root), NULL, key);
    
    if (t->root->key == key) return 1;

    int b = 0;
    // insere na sub-árvore root
    return insert_key_by_node(&(t->root), t->root, key, &b);
}

// procura uma chave na árvore, retorna 0 em caso de erro e !0 caso contrário
int search_key_avl(avl_t *t, key_t key){
    if (tree_is_empty(t)) return 0;

    // caso ja ache a chave na root
    if (t->root->key == key) return 1;

    // busca recursivamente
    if (t->root->key > key) // esquerda
        return search_key_by_node(t->root->left, key);
    else // direita
        return search_key_by_node(t->root->right, key);

    return 1;
}

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int print_tree_avl(avl_t *t){
    if (tree_is_empty(t)) return 1;

    // imprime a árvore recursivamente
    print_tree_by_node(t->root);
    printf("\n");
    
    return 1;
}


// imprime a representação de parenteses de uma árvore binária
int print_parethesis(avl_t *t) {
    if (tree_is_empty(t)) return 1;

    // imprime a árvore recursivamente
    print_parenthesis_by_node(t->root);
    printf("\n");
    
    return 1;
}

int print_with_height(avl_t *t){
    if (tree_is_empty(t)) return 1;

    // imprime a árvore recursivamente
    return print_with_height_by_node(t->root, 0);
}

int print_graph(avl_t *t){
    if (tree_is_empty(t))return 1;

    print_graph_by_node(t->root, 1);
    printf("\n");
    return 1; 
}

// retorna uma string com a notação de parenteses da árvore
int string_parenthesis(avl_t *t, char * str, int max){
    if (tree_is_empty(t)) return 1;

    // adiquire a árvore recursivamente
    return string_parenthesis_by_node(t->root, str, 0, max);
}

// retorna uma string com a notação de parenteses da árvore
int string_height(avl_t *t, char * str, int max){
    if (tree_is_empty(t)) return 1;

    // adiquire a árvore recursivamente
    return string_height_by_node(t->root, str, 0, max, 0);
}

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_avl(avl_t *t, key_t key){
    if (tree_is_empty(t)) return 0;

    // remove a chave em root
    if (t->root->key == key) {
        remove_node(t->root, &(t->root));
        return 1;
    }

    // remove a chave na sub-árvore correspondente
    if (t->root->key > key) // esquerda
        remove_key_by_node(t->root->left, &(t->root->left),key);
    else  // direita 
        remove_key_by_node(t->root->right, &(t->root->right), key);

    balance_to_key(&(t->root), key);
    
    return 1;
}

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_avl(avl_t *t){
    if (tree_is_empty(t)) return 1;

    // empilha todos os nodos e os destroi recursivamente
    destroy_tree(&(t->root));
    t->root = NULL;

    return 1;
}

// retorna o numero total de nodos
int tree_size(avl_t *t){
    if (tree_is_empty(t)) return 0;

    // descobre o tamanho da árvore recursivamente
    int size = 1;
    number_of_nodes(t->root, &size);
    return size;
}

int tree_height(avl_t *t){
    if (!t->root) return 0;
    return height_by_node(t->root, 0);
}