#ifndef AVL_OPS
#define AVL_OPS

#include "avl_module.h"

/* 
    AVL Operations:
    Descreve operacoes que diferenciam a AVL das outras arvores
*/

// retorna o fator de balanceamento da subárvore
int balance_factor(node_t *nd);

// rotaciona a árvore para realizar seu balanço
int rotate_right(node_t **nd);
int rotate_left(node_t **nd);
int rotate(node_t **nd);

// ajusta o fator de balanceamento nos nodos ascendentes
int adjust_bf_upwards(node_t *nd);

// desde root, confere e ajusta o balanço de cada nodo até uma chave específica
int balance_to_key(node_t **nd, key_t key);

#endif