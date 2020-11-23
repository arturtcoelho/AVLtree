#include <stdio.h>
#include <math.h>

#include "avl_module.h"

// imprime recursivamente in-order as chaves da árvore
void print_tree_by_node(node_t *nd){
    if (nd == NULL) return; // terminou essa sub-árvore

    print_tree_by_node(nd->left); // imprime a sub-árvore a esquerda
    printf("%d ", nd->key);
    print_tree_by_node(nd->right); // imprime a sub-árvore a direita

    return;
}

// imprime na saída padrão a sub-árvore na notação de arenteses
int print_parenthesis_by_node(node_t *nd){
    if (nd == NULL) return 0; // terminou essa sub-árvore

    printf("(%d", nd->key);
    print_parenthesis_by_node(nd->left);
    print_parenthesis_by_node(nd->right);
    printf(")");

    return 1;
}

// imprime in-order com a altura
int print_with_height_by_node(node_t *nd, int h){
    if (!nd) return 0;

    print_with_height_by_node(nd->left, h+1);
    printf("%d,%d\n", nd->key, h);
    print_with_height_by_node(nd->right, h+1);

    return 1;
}

// imprime graficamente
int print_graph_by_node(node_t *nd, int h){
    if (!nd) return printf("\n");

    print_graph_by_node(nd->right, h+1);
    for (int i = 0; i < (h-1)*SPACING; i++) printf(" ");
    if (nd->top){
        if (nd->top->left == nd)
            printf("\\");
        else
            printf("/");
    }
    printf(" %d", nd->key);
    
    print_graph_by_node(nd->left, h+1);

    return 1;
}

// escreve as chaves em str com notação de parenteses
int string_parenthesis_by_node(node_t *nd, char *str, int i, int max){
    if (!nd) return 0;

    // confere se a posição i somada a quantidade de números a ser impressa
    // somada aos parenteses ultrapassa o maximo permitido do buffer
    int added = (ceil(log10(nd->key > 0 ? nd->key : 1)) + 2);
    if (i + added >= max){
        fprintf(stderr, "TOO LARGE INPUT TO BUFFER, tried to add %d on top of %d, maxing %d", added, i, max);
        return 0;
    }

    int res = i;
    res += sprintf(str+res, "(%d", nd->key);
    res += string_parenthesis_by_node(nd->left, str, res, max);
    res += string_parenthesis_by_node(nd->right, str, res, max);
    res += sprintf(str+res, ")");

    return res-i;
}

// escreve em str com altura
int string_height_by_node(node_t *nd, char *str, int i, int max, int h){
    if (!nd) return 0;
    // confere se a posição i somada a quantidade de números a ser impressa
    // somada aos parenteses ultrapassa o maximo permitido do buffer
    int added = (log10(nd->key > 0 ? nd->key : 1) + 3);

    if (i + added >= max){
        fprintf(stderr, "TOO LARGE INPUT TO BUFFER, tried to add %d on top of %d, maxing %d", added, i, max);
        return 0;
    }

    int res = i;
    res += string_height_by_node(nd->left, str, res, max, h+1);
    res += sprintf(str+res, "%d,%d ", nd->key, h);
    res += string_height_by_node(nd->right, str, res, max, h+1);
    return res-i;
}