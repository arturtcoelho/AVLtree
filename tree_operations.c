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
    // caso esse nodo seja nulo, insere nele
    if (!*nd) return insert_key(nd, top, key);

    // caso esse nodo ja esteja ocupado, insere em um de seus filhos
    int res = 1;
    if ((*nd)->key > key){
        if (DEV) {fprintf(stderr, "Inserindo key: %d em %p\n", key, &((*nd)->left));}
        res = insert_key_by_node(&((*nd)->left), *nd, key);
    } else {
        if (DEV) {fprintf(stderr, "Inserindo key: %d em %p\n", key, &((*nd)->right));}   
        res = insert_key_by_node(&((*nd)->right), *nd, key);
    }

    // caso não seja possivel inserir, retorna 0
    if (!res) return 0;

    // realiza o giro da árvore para se manter balanceda
    rotate();

    return 1;
}

// adiciona uma chave no nodo especificado, com o pai
int insert_key(node_t **nd, node_t *top, key_t key){
    if (DEV) {fprintf(stderr, "Inserindo folha em %p\n", nd);}
    
    // aloca memória para o nodo
    *nd = (node_t*)malloc(sizeof(node_t));
    if (!nd) bad_malloc();

    // atribui os ponteiros das folhas
    (*nd)->top = top;
    (*nd)->left = NULL;
    (*nd)->right = NULL;
    (*nd)->key = key;

    return 1;
}

int search_key_by_node(node_t *nd, key_t key){
    if (nd == NULL) return 0; // caso seja nulo, não achou
    if (nd->key == key) return 1; // achou
    if (nd->key > key) { // procura a esquerda
        return search_key_by_node(nd->left, key);
    } else { // procura a direita
        return search_key_by_node(nd->right, key);
    }
}

void print_tree_by_node(node_t *nd){
    if (nd == NULL) return; // terminou essa sub-árvore
    print_tree_by_node(nd->left); // imprime a sub-árvore a esquerda
    printf("%d ", nd->key);
    print_tree_by_node(nd->right); // imprime a sub-árvore a direita
    return;
}