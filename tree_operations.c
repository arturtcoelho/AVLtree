#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"

// função de auxílio para casos de alocação dinâmica
void bad_malloc(){
    fprintf(stderr, "Erro de alocação");
    exit(1);
}

// retorna a 0 caso a árvore estaja vazia e !0 caso contrário 
int tree_is_empty(avl_t *t){
    return (t->root == NULL);
}

// insere uma chave em um nodo apontado, retorna 1 em caso de sucesso, 0 ao contrário
int insert_key_by_node(node_t **nd, node_t *top, key_t key, int *should_balance){
    // caso esse nodo seja nulo, insere nele
    if (!*nd) {
        insert_key(nd, top, key);
        *should_balance = 1;
        return 1; 
    }

    if ((*nd)->key == key) return 1; // caso o número ja exista

    // caso esse nodo ja esteja ocupado, insere em um de seus filhos e
    // ajusta o balanceamento dos nodos por qual ele passa 
    if ((*nd)->key > key){
        insert_key_by_node(&((*nd)->left), *nd, key, should_balance);
        if (*should_balance) (*nd)->bf--;
    } else {
        insert_key_by_node(&((*nd)->right), *nd, key, should_balance);
        if (*should_balance) (*nd)->bf++;
    }
    // confere balanceamento da árvore
    if (*should_balance) {
        if (!(*nd)->bf) *should_balance = 0;
        if (abs((*nd)->bf) > 1) {
            rotate(nd);
            *should_balance = 0;
        }
    }
    return 1;
}

// adiciona uma chave no nodo especificado, com o pai
int insert_key(node_t **nd, node_t *top, key_t key){
    
    // aloca memória para o nodo
    *nd = (node_t*)malloc(sizeof(node_t));
    if (!nd) bad_malloc();

    // atribui os ponteiros das folhas
    (*nd)->top = top;
    (*nd)->left = NULL;
    (*nd)->right = NULL;
    (*nd)->key = key;
    (*nd)->bf = 0;

    return 1;
}

// procura a chave 'key' a partir de um nodo apontado, 1 se a chave esta presente e 0 caso contrario
int search_key_by_node(node_t *nd, key_t key){
    if (nd == NULL) return 0; // caso seja nulo, não achou

    if (nd->key == key) return 1; // achou

    if (nd->key > key) { // procura a esquerda
        return search_key_by_node(nd->left, key);
    } else { // procura a direita
        return search_key_by_node(nd->right, key);
    }
}

// função para o caso onde ambos os filhos estão presentes
int remove_both_exist(node_t *nd){
    if (!nd) return 0; // caso o nodo não exista

    node_t *succ = min_node(nd->right); // succ = sucessor de nodo
    nd->key = succ->key; // copia a chave
    if (succ == nd->right) { // caso especial onde subárvore da direita é o sucessor
        remove_node(succ, &(nd->right));
    } else { // remove o sucessor
        remove_node(succ, &(succ->top->left));
    }
    return 1;
}

// remove o nodo apontado
int remove_node(node_t *nd, node_t **top){
    // se nodo não existir
    if (!nd) return 0;

    if (nd->left && nd->right) { // ambos os filhos existem
        remove_both_exist(nd);
        return 1;
    } else {
        if (!(nd->left || nd->right)) { // nenhum filho existte
            if (nd->top){
                if (nd->top->left == nd) {
                    nd->top->bf++;
                    if (!nd->top->right) adjust_bf_upwards(nd->top);
                } else {
                    nd->top->bf--;
                    if (!nd->top->left) adjust_bf_upwards(nd->top);
                }
            } 
            *top = NULL;
            free(nd);
        } else { // uma das duas existe
            adjust_bf_upwards(nd);

            // reatribui o ponteiro do pai para o novo filho
            *top = nd->left ? nd->left : nd->right;

            // ajusta o ponteiro do filho para o pai
            if (nd->left){
                nd->left->top = nd->top;
            } else {
                nd->right->top = nd->top;
            }
            free(nd);
        }
    }
    return 1;
}

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, node_t **top, key_t key){
    if (!nd) return 0;

    if (nd->key == key) return remove_node(nd, top);

    if (nd->key > key) //esquerda
        return remove_key_by_node(nd->left, &(nd->left), key);
    else // direita
        return remove_key_by_node(nd->right, &(nd->right), key);

    return 0;
}

// destroi a árvore recursivamente
int destroy_tree(node_t **nd){
    if (!*nd) return 1; // se ja não existe, retorna

    destroy_tree(&((*nd)->left)); // destroi a sub-arvore da esquerda
    (*nd)->left = NULL; // define a folha como vazia já

    destroy_tree(&((*nd)->right)); // destroi a sub-árvore da direita
    (*nd)->right = NULL; // define a folha como vazia

    free(*nd); // libera o nodo em si
    return 1;
}

// retorna o ponteiro para o nodo com o menor valor da subárvore passada, ou null caso tenha sido passado null
node_t *min_node(node_t *nd){
    if (!nd) return NULL;
    if (!nd->left) return nd;
    return (min_node(nd->left));
}

// retorna o ponteiro para o nodo com o maior valor da subárvore passada, ou null caso tenha sido passado null
node_t *max_node(node_t *nd){
    if (!nd) return NULL;
    if (!nd->right) return nd;
    return (max_node(nd->right));
}

// bool, retorna verdadeiro caso seja o maior nodo da árvore, falso caso contrário
int last_right_node(node_t *nd){
    if (!nd->top) return 1;
    if (nd->top->right == nd) return last_right_node(nd->top);
    return 0;
}

// retorna o número de nodos da sub-árvore
int number_of_nodes(node_t *nd, int *size){
    if (!nd) return 0;
    *size += number_of_nodes(nd->left, size);
    *size += number_of_nodes(nd->right, size);
    return 1;
}

// calcula a altura de uma subárvore
int height_by_node(node_t *nd, int height){
    if (!nd) return height;
    int left_height = height_by_node(nd->left, height);
    int right_height = height_by_node(nd->right, height);
    return left_height > right_height ? left_height + 1 : right_height + 1;
}