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

// imprime recursivamente in-order as chaves da árvore
void print_tree_by_node(node_t *nd){
    if (nd == NULL) return; // terminou essa sub-árvore
    print_tree_by_node(nd->left); // imprime a sub-árvore a esquerda
    printf("%d ", nd->key);
    print_tree_by_node(nd->right); // imprime a sub-árvore a direita
    return;
}

// remove o nodo apontado
int remove_node(node_t *nd, node_t **top){
    // se nodo não existir
    if (!nd) return 0;

    if(DEV) {fprintf(stderr, "Removendo nodo %p (%d)\n", nd, nd->key);}
    
    if (nd->left && nd->right) { // ambos os filhos existem
        if(DEV) {fprintf(stderr, "Removendo nodo AMBOS EXISTEM %p (%d)\n", nd, nd->key);}
        node_t *succ = min_node(nd->right); // succ = sucessor de nodo
        nd->key = succ->key; // copia a chave PODE SER MUDADO PARA UMA ATRIBUIÇÃO DE PONTEIROS
        if (succ == nd->right){ // caso especial onde subárvore da direita é o sucessor
            nd->right = NULL;
        } else { // remove o sucessor
            succ->top->left = NULL;
        }
        free(succ);
        return 1;
    } else {
        if (!(nd->left || nd->right)) { // nenhum filho existte
            if(DEV) {fprintf(stderr, "Removendo nodo NENHUM EXISTE %p (%d)\n", nd, nd->key);}
            free(nd);
            if (top) *top = NULL;
            return 1;
        } else { // uma das duas existe
            if(DEV) {fprintf(stderr, "Removendo nodo UMA EXISTE %p (%d)\n", nd, nd->key);}
            if (top) *top = nd->left ? nd->left : nd->right; // o nodo passa a ser o filho existente
            free(nd);
            return 1;
        }
    }
    return 0;
}

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, node_t **top, key_t key){
    if (!nd) return 0;

    if (nd->key == key) {
        if (DEV) {fprintf(stderr, "Removendo nodo %p com chave %d\n", nd, key);}
        return remove_node(nd, top);
    }

    if (DEV) {fprintf(stderr, "Removendo nodo %p com chave %d\n", nd, key);}
    if (nd->key > key) { //esquerda
        if (DEV) {fprintf(stderr, "Removendo nodo esquerdo %p com chave %d\n", nd->left, key);}
        return remove_key_by_node(nd->left, &(nd->left), key);
    } else { // direita
        if (DEV) {fprintf(stderr, "Removendo nodo direito %p com chave %d\n", nd->right, key);}
        return remove_key_by_node(nd->right, &(nd->right), key);
    }

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
    if (DEV) {fprintf(stderr, "Buscando min %p (%d) e top %p (%d)\n", nd, nd->key, nd->top, nd->top->key);}
    if (!nd) return NULL;
    if (!nd->left) {
        if (DEV) {fprintf(stderr, "Achou min %p (%d), com top %p (%d)\n", nd, nd->key, nd->top, nd->top->key);} 
        return nd;
    }
    return (min_node(nd->left));
}

// retorna o ponteiro para o nodo com o maior valor da subárvore passada, ou null caso tenha sido passado null
node_t *max_node(node_t *nd){
    if (!nd) return NULL;
    if (!nd->right) return nd;
    return (max_node(nd->right));
}
