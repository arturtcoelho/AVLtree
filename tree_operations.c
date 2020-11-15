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
int remove_node(node_t *nd){
    // se nodo não existir
    if (!nd) return 0;

    if(DEV) {fprintf(stderr, "Removendo nodo %p (%d)\n", nd, nd->key);}
    
    if (nd->left && nd->right) { // ambos os filhos existem
        if(DEV) {fprintf(stderr, "Removendo nodo AMBOS EXISTEM %p (%d)\n", nd, nd->key);}
        node_t *succ = min_node(nd->right); // succ = sucessor de nodo
        nd->key = succ->key; // copia a chave
        if (succ == nd->right){ // caso especial onde subárvore da direita é o sucessor
            node_t *temp = nd->right;
            if (nd->right->right) nd->right->right->top = nd;
            nd->right = nd->right->right;
            free(temp);
        } else { // remove o sucessor
            succ->top->left = succ->right;
            if (succ->right) succ->right->top = succ->top;
            free(succ);
        }
        return 1;

    } else {
        if (!(nd->left || nd->right)) { // nenhum filho existte
            // if(DEV) {fprintf(stderr, "Removendo nodo NENHUM EXISTE %p (%d)\n", nd, nd->key);}
            if(DEV) {fprintf(stderr, "NENHUM EXISTE %p (%d), left (%d), right (%d), top (%d)\n", nd, nd->key, nd->left ? nd->left->key : 0, nd->right ? nd->right->key : 0, nd->top ? nd->top->key : 0);}
            if (nd->top) { // não é raiz
                if (nd->top->left == nd) { // esquerda
                    nd->top->left = NULL;
                } else { // direita
                    nd->top->right = NULL;
                }
            } else { // é root
                printf("É ROOT\n");
                return 1;
            }
            free(nd);
            return 1;
        } else { // uma das duas existe
            if (nd->top) { // se top existe
                if(DEV) {fprintf(stderr, "Removendo nodo UMA EXISTE %p (%d)\n", nd, nd->key);}
                if (nd->top->left == nd) { // se tem esquerdo
                    // if(DEV) {fprintf(stderr, "Removendo nodo %p (%d), left (%d), right (%d), top (%d)\n", nd, nd->key, nd->left ? nd->left->key : 0, nd->right ? nd->right->key : 0, nd->top ? nd->top->key : 0);}
                    nd->top->left = nd->left ? nd->left : nd->right;
                } else { // se tem direito
                    nd->top->right = nd->left ? nd->left : nd->right;       
                }
                if (nd->left) {
                    nd->left->top = nd->top;
                } else {
                    nd->right->top = nd->top;
                }
                free(nd);
                return 1;
            } else { // é root
                if(DEV) {fprintf(stderr, "Removendo nodo UMA EXISTE (%d), %s\n", nd->key, nd->left ? "ESQ" : "DIR");}
                node_t *temp;
                if (nd->left) { // esquerda
                    if(DEV) {fprintf(stderr, "Ajustando ESQ (%d)\n", nd->left->key);}
                    temp = nd->left;
                    if(nd->left->left) nd->left->left->top = nd;
                    if(nd->left->right) nd->left->right->top = nd;

                    nd->key = temp->key;
                    nd->left = temp->left;
                    nd->right = temp->right;
                    free(temp);
                } else { // direita
                    if(DEV) {fprintf(stderr, "Ajustando DIR (%d)\n", nd->right->key);}
                    temp = nd->right;
                    if(nd->right->left) nd->right->left->top = nd;
                    if(nd->right->right) nd->right->right->top = nd;

                    nd->key = temp->key;
                    nd->left = temp->left;
                    nd->right = temp->right;
                    free(temp);
                }
                if(DEV){fprintf(stderr, "nd, key: %d, left: %d, right: %d,top: %d\n", nd->key, nd->left ? nd->left->key : 0, nd->right ? nd->right->key : 0, nd->top ? nd->top->key : 0);}
                return 1;
            }
        }
    }
    return 0;
}

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, key_t key){
    if (!nd) return 0;

    if (nd->key == key) {
        if (DEV) {fprintf(stderr, "Removendo (pois achou) o nodo %p com chave %d\n", nd, key);}
        return remove_node(nd);
    }

    if (DEV) {fprintf(stderr, "Removendo nodo %p (de chave %d) procurando chave %d\n", nd, nd->key, key);}
    if (nd->key > key) { //esquerda
        if (DEV) {fprintf(stderr, "Removendo nodo esquerdo %p com chave %d\n", nd->left, key);}
        return remove_key_by_node(nd->left, key);
    } else { // direita
        if (DEV) {fprintf(stderr, "Removendo nodo direito %p com chave %d\n", nd->right, key);}
        return remove_key_by_node(nd->right, key);
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
