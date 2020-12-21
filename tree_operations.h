#ifndef __AVL_OPERATOR__
#define __AVL_OPERATOR__

#include "avl_module.h"

/*
    Tree Operations:
    Descreve operacoes usadas por estruturas de arvores, em geral
*/

// retorna 0 caso a árvore esteja vazia, !0 caso contrário 
int tree_is_empty(avl_t *t);

// insere uma chave no nodo especificado, com o pai
int insert_key(node_t **nd, node_t *top, key_t key);

// insere a chave 'key' a partir um nodo apontado, retorna 1 em caso de sucesso, 0 caso contrário
int insert_key_by_node(node_t **top, node_t *nd, key_t key, int *should_balance);

// procura a chave 'key' a partir de um nodo apontado, 1 se a chave esta presente e 0 caso contrario
int search_key_by_node(node_t *nd, key_t key);

// imprime recursivamente as chaves da árvore
void print_tree_by_node(node_t *nd);
int print_parenthesis_by_node(node_t *nd);
int print_with_height_by_node(node_t *nd, int h);
int print_graph_by_node(node_t *nd, int h);

// escreve nas strings passadas as chaves da aŕvore, assume uma string de tamanho suficiente
int string_parenthesis_by_node(node_t *nd, char *str, int i, int max);
int string_height_by_node(node_t *nd, char *str, int i, int max, int h);

// remove o nodo apontado
int remove_node(node_t *nd, node_t **top);
int remove_root(avl_t *t);

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, node_t **top,key_t key);

// destroi a árvore recursivamente
int destroy_tree(node_t **nd);

// retorna o ponteiro para o nodo com o menor/maior valor da subárvore passada, ou null caso tenha sido passado null
node_t *min_node(node_t *nd);
node_t *max_node(node_t *nd);

// retorna !0 caso seja o maior nodo da subárvore, 0 caso contrário
int last_right_node(node_t *nd);

// retorna o numero de nodos
int number_of_nodes(node_t *nd, int *size);

// retorna a altura de uma subárvore
int height_by_node(node_t *nd, int height);

#endif