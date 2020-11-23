#include <stdlib.h>
#include <stdio.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"

int balance_factor(node_t *nd){
    if (!nd) return 0;
    int left_height = height_by_node(nd->left, 0);
    int right_height = height_by_node(nd->right, 0);
    return right_height - left_height;
}

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

int balance_up(node_t *nd){
    if (!nd->top || abs(nd->bf) > 1) return 1;
    if (nd->top->left == nd) {
        nd->top->bf++;
    }
    else {
        nd->top->bf--;
    }
    balance_up(nd->top);
    return 1;
}

// rotaciona a árvore para realizar seu balanço
int rotate(node_t **nd, int *bal){
    if ((*nd)->bf == -2) { //desbalanceado na  esquerda
        printf("Rotacionando %d a direita\n", (*nd)->key);
        if ((*nd)->left != NULL && (*nd)->left->bf > 0) {
            printf("Rotacionando %d a esquerda antes\n", (*nd)->left->key);
            rotate_left(&((*nd)->left));
        }
        rotate_right(nd);        
    } else { // desbalanceado a direita
        printf("Rotacionando %d a esquerda\n", (*nd)->key);
        if ((*nd)->right->bf < 0){
            printf("Rotacionando %d a direita antes\n", (*nd)->right->key);
            rotate_right(&((*nd)->right));
        }
        rotate_left(nd);
    }
    (*nd)->bf = 0;
    *bal = 0;
    (*nd)->left->bf = balance_factor(*nd);
    (*nd)->right->bf = balance_factor(*nd);
    return 1;
}