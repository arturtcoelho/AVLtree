#ifndef AVL_OPS
#define AVL_OPS

#include "avl_module.h"

// retorna o fator de balanceamento da subárvore
int balance_factor(node_t *nd);

int rotate_right(node_t **nd);
int rotate_left(node_t **nd);

// rotaciona a árvore para realizar seu balanço
int rotate(node_t **nd, int *bal);

int balance_up(node_t *nd);

#endif