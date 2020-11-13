#ifndef __AVL_OPERATOR__
#define __AVL_OPERATOR__

#include "avl_tree.h"

// retorna 1 caso a árvore ja tenha sido inicializada, 0 caso contrário 
int tree_is_empty(avl_t *t);

// insere uma chave no nodo especificado, com o pai
int insert_key(node_t **nd, node_t *top, key_t key);

// insere a chave 'key' a partir um nodo apontado, retorna 1 em caso de sucesso, 0 caso contrário
int insert_key_by_node(node_t **top, node_t *nd, key_t key);

// procura a chave 'key' a partir de um nodo apontado, 1 se a chave esta presente e 0 caso contrario
int search_key_by_node(node_t *nd, key_t key);

// imprime recursivamente in-order as chaves da árvore
void print_tree_by_node(node_t *nd);

// remove o nodo apontado
int remove_node(node_t *nd, node_t **top);

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, node_t **top, key_t key);

// destroi a árvore recursivamente
int destroy_tree(node_t **nd);

// retorna o ponteiro para o nodo com o menor/maior valor da subárvore passada, ou null caso tenha sido passado null
node_t *min_node(node_t *nd);
node_t *max_node(node_t *nd);

#endif