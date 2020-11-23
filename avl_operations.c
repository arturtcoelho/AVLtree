#include <stdlib.h>
#include <stdio.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"

// calcula o fator de balanceamento de dado nodo
int balance_factor(node_t *nd){
    int left_height = height_by_node(nd->left, 0);
    int right_height = height_by_node(nd->right, 0);
    return right_height - left_height;
}

// rotaciona nd para a direita
int rotate_right(node_t **nd){
    node_t *r = (*nd)->left;
    r->top = (*nd)->top;
    (*nd)->left = r->right;
    if ((*nd)->left) (*nd)->left->top = *nd;
    r->right = *nd;
    (*nd)->top = r;
    (*nd) = r;

    return 1;
}

// rotaciona nd para a esquerda
int rotate_left(node_t **nd){
    node_t *r = (*nd)->right;
    r->top = (*nd)->top;
    (*nd)->right = r->left;
    if ((*nd)->right) (*nd)->right->top = *nd;
    r->left = *nd;
    (*nd)->top = r;
    (*nd) = r;

    return 1;
}

// ajusta o fator de balanceamento para os nodos anteriores a nd
int adjust_bf_up(node_t *nd){
    if (!nd->top || abs(nd->bf) > 1) return 1;
    if (nd->top->left == nd) {
        nd->top->bf++;
    }
    else {
        nd->top->bf--;
    }
    adjust_bf_up(nd->top);
    return 1;
}

// rotaciona a árvore para realizar seu balanço
int rotate(node_t **nd, int *bal){
    if ((*nd)->bf == -2) { //desbalanceado na  esquerda
        if ((*nd)->left != NULL && (*nd)->left->bf > 0) {
            rotate_left(&((*nd)->left));
        }
        rotate_right(nd);        
    } else { // desbalanceado a direita
        if ((*nd)->right->bf < 0){
            rotate_right(&((*nd)->right));
        }
        rotate_left(nd);

    }
    *bal = 0;
    (*nd)->bf = balance_factor((*nd));
    (*nd)->left->bf = balance_factor((*nd)->left);
    (*nd)->right->bf = balance_factor((*nd)->right);
    return 1;
}

// desde root, confere e ajusta o balanço de cada nodo até uma chave específica
int balance_to_key(node_t **nd, key_t key){
    if (!*nd) return 1;
    int b;
    if (abs((*nd)->bf) > 1) rotate(nd, &b);

    if ((*nd)->key > key) {
        balance_to_key(&((*nd)->left), key);
    } else {
        balance_to_key(&((*nd)->right), key);
    }
    return 1;
}