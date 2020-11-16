#ifndef AVL_MODULE
#define AVL_MODULE

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include "avl_tree.h"

avl_t *tree = NULL;
char *parenthesis_tree = "";
int height = 0;
int num_nodes = 0;

int teste();

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
void initialize_avl(){
    if (tree) free(tree);
    tree = (avl_t*)malloc(sizeof(avl_t));
    if (!tree) {
        fprintf(stderr, "ERR MALLOC\n");
        exit(1);
    }
    if(!_initialize_avl(tree)){
        fprintf(stderr, "ERR INITIALIZE\n");
        exit(1);
    }
    return;
}

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
void insert_key_avl(key_t key){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return;
    }

    if (!_insert_key_avl(tree, key)){
        fprintf(stderr, "ERR INSERTING IN TREE (%d)\n", key);
    }
    return;
}

// procura uma chave key na árvore, retorna 0 em caso de erro e !0 caso contrário
int search_key_avl( key_t key){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return 0;
    }
    return _search_key_avl(tree, key);
}

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
void print_tree_avl(){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return;
    }
    _print_tree_avl(tree);
    return;
}

void print_parethesis(){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return;
    }
    _print_parethesis(tree);
    return;
}

// escreve em str a árvore em notação de parenteses, retorna o número de caracteres escritos
// int string_parenthesis(char *str, int max){
//     if (!tree) {
//         fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
//         return;
//     }

// }

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
void remove_key_avl(key_t key){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return;
    }
    if (!_remove_key_avl(tree, key)){
        fprintf(stderr, "ERR REMOVING KEY %d\n", key);
        return;
    }
}

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
void destroy_tree_avl(){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return;
    }
    _destroy_tree_avl(tree);
    free(tree);
}

int tree_size(){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return 0;
    }
    return _tree_size(tree);
}

int tree_height(){
    if (!tree) {
        fprintf(stderr, "ERR TREE NOT INITIALIZED\n");
        return 0;
    }
    return _tree_height(tree);
}

#endif