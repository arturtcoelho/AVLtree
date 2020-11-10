#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "avl_tree.h"
#include "tree_operations.h"

// função de auxílio para casos de alocação dinâmica
void bad_malloc(){
    fprintf(stderr, "Erro de alocação");
    exit(1);
}

// rotaciona a árvore para realizar seu balanço
int rotate(){
    return 1;
}

// retorna !0 caso a árvore ja tenha sido inicializada, 0 caso contrário 
int tree_is_empty(avl_t *t){
    return (t->root == NULL);
}

// insere uma chave em um nodo apontado, retorna 1 em caso de sucesso, 0 ao contrário
int insert_key_by_node(node_t **nd, node_t *top, key_t key){
    if (!*nd){
        return insert_key(nd, top, key);
    }

    int res = 1;
    if ((*nd)->key > key){
        res = insert_key_by_node(&((*nd)->left), *nd, key);
    } else {
        res = insert_key_by_node(&((*nd)->right), *nd, key);
    }

    if (!res) return 0;

    rotate();

    return 1;
}

// adiciona uma chave no nodo especificado, com o pai
int insert_key(node_t **nd, node_t *top, key_t key){
    if (DEV) {
        fprintf(stderr, "Inserindo em %p\n", nd);
    }
    *nd = (node_t*)malloc(sizeof(node_t));
    if (!nd) bad_malloc();

    (*nd)->top = top;
    (*nd)->left = NULL;
    (*nd)->right = NULL;
    (*nd)->key = key;

    return 1;
}

int search_key_by_node(node_t *nd, key_t key){
    if (nd == NULL) return 0;
    if (nd->key == key) return 1;
    if (nd->key > key) {
        return search_key_by_node(nd->left, key);
    } else {
        return search_key_by_node(nd->right, key);
    }
}

void print_tree_by_node(node_t *nd){
    if (nd == NULL) return;
    print_tree_by_node(nd->left);
    printf("%d ", nd->key);
    print_tree_by_node(nd->right);
}