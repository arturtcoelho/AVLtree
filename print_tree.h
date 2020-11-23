#ifndef PRINT_TREE_OPS
#define PRINT_TREE_OPS

#include "avl_module.h"

// imprime recursivamente as chaves da árvore
void print_tree_by_node(node_t *nd);
int print_parenthesis_by_node(node_t *nd);
int print_with_height_by_node(node_t *nd, int h);
int print_graph_by_node(node_t *nd, int h);

// escreve em str as chaves da árvore
int string_parenthesis_by_node(node_t *nd, char *str, int i, int max);
int string_height_by_node(node_t *nd, char *str, int i, int max, int h);

#endif