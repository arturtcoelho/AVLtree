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
    (*nd)->left->bf = height_by_node((*nd)->left->right, 0) - height_by_node((*nd)->left->left, 0);
    (*nd)->right->bf = height_by_node((*nd)->right->right, 0) - height_by_node((*nd)->right->left, 0);
    return 1;
}


// retorna !0 caso a árvore ja tenha sido inicializada, 0 caso contrário 
int tree_is_empty(avl_t *t){
    return (t->root == NULL);
}

// insere uma chave em um nodo apontado, retorna 1 em caso de sucesso, 0 ao contrário
int insert_key_by_node(node_t **nd, node_t *top, key_t key, int *bal){
    // caso esse nodo seja nulo, insere nele
    if (!*nd) {
        insert_key(nd, top, key);
        *bal = 1;
        return 1; 
    }

    if ((*nd)->key == key) return 0; // caso o número ja exista

    // caso esse nodo ja esteja ocupado, insere em um de seus filhos
    if ((*nd)->key > key){
        insert_key_by_node(&((*nd)->left), *nd, key, bal);
        if (*bal) (*nd)->bf--;
    } else {
        insert_key_by_node(&((*nd)->right), *nd, key, bal);
        if (*bal) (*nd)->bf++;
    }
    if (*bal) {
        if (!(*nd)->bf) *bal = 0;
        if (abs((*nd)->bf) > 1) {
            rotate(nd, bal);
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

    if (nd->key > key) // procura a esquerda
        return search_key_by_node(nd->left, key);
    else // procura a direita
        return search_key_by_node(nd->right, key);
}

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

int print_with_height_by_node(node_t *nd, int h){
    if (!nd) return 0;

    print_with_height_by_node(nd->left, h+1);
    printf("%d,%d\n", nd->key, h);
    print_with_height_by_node(nd->right, h+1);

    return 1;
}

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
    printf(" %d(%d)", nd->key, nd->bf);
    // printf(" (%d)%d(%d)", nd->top?nd->top->key:-1,nd->key, nd->bf);
    
    print_graph_by_node(nd->left, h+1);

    return 1;
}

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

// função para o caso onde ambos os filhos estão presentes
int remove_both_exist(node_t *nd){
    if (!nd) return 0; // caso o nodo não exista

    node_t *succ = min_node(nd->right); // succ = sucessor de nodo
    nd->key = succ->key; // copia a chave
    if (succ == nd->right){ // caso especial onde subárvore da direita é o sucessor
        node_t *temp = nd->right; // guarda o nodo a ser retirado

        // atribui o filho da direita do filho da direita aponta para o novo nodo 
        if (nd->right->right) nd->right->right->top = nd; 
        // passa o filho da direita para o filho do filho da direita
        nd->right = nd->right->right;
        free(temp);
    } else { // remove o sucessor
        succ->top->left = succ->right; // reatribui os ponteiros do sucessor
        if (succ->right) succ->right->top = succ->top;
        free(succ);
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
            if (nd->top) nd->top->bf += nd->top->left == nd ? 1 : -1;
            balance_up(nd->top);
            *top = NULL;
            free(nd);
            return 1;
        } else { // uma das duas existe
            balance_up(nd);
            // reatribui o ponteiro do pai para o novo filho
            *top = nd->left ? nd->left : nd->right;

            // ajusta o ponteiro do filho para o pai
            if (nd->left)
                nd->left->top = nd->top;
            else
                nd->right->top = nd->top;
            
            free(nd);
            return 1;
        }
    }
    return 0;
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

int last_right_node(node_t *nd){
    if (!nd->top) return 1;
    if (nd->top->right == nd) return last_right_node(nd->top);
    return 0;
}

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