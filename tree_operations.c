#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "tree_module.h"
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
int tree_is_empty(tree_t *t){
    return (t->root == NULL);
}

// insere uma chave em um nodo apontado, retorna 1 em caso de sucesso, 0 ao contrário
int insert_key_by_node(node_t **nd, node_t *top, key_t key){
    // caso esse nodo seja nulo, insere nele
    if (!*nd) return insert_key(nd, top, key);

    if ((*nd)->key == key) {
        if (DEV) {fprintf(stderr, "Inserindo key: %d, valor ja existe\n", key);}
        return 1;
    }

    // caso esse nodo ja esteja ocupado, insere em um de seus filhos
    int res = 1;
    if ((*nd)->key > key){
        if (DEV) {fprintf(stderr, "Inserindo key: %d esquerda\n", key);}
        res = insert_key_by_node(&((*nd)->left), *nd, key);
    } else {
        if (DEV) {fprintf(stderr, "Inserindo key: %d direita\n", key);}   
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
    if (DEV) {fprintf(stderr, "Inserindo folha em top (%d)\n", (*nd)->top ? (*nd)->top->key : 0);}
    
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

// imprime na saída padrão a sub-árvore na notação de arenteses
int print_parenthesis_by_node(node_t *nd){
    if (nd == NULL) {
        return 0; // terminou essa sub-árvore
    }
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
    if (nd) {
        print_graph_by_node(nd->right, h+1);

        for (int i = 0; i < (h-1)*SPACING; i++) {
            printf(" ");
        }
        if (nd->top){
            if (nd->top->left == nd){
                printf("\\");
            } else {
                printf("/");
            }
        }

        printf(" %-*d", MAX_NUM_LEN,  nd->key);

        print_graph_by_node(nd->left, h+1);

        return 1;
    }
    printf("\n");
    return 0;
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

    if(DEV) {fprintf(stderr, "Removendo nodo AMBOS EXISTEM (%d)\n", nd->key);}

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
int remove_node(node_t *nd){
    // se nodo não existir
    if (!nd || !nd->top) return 0;

    if(DEV) {fprintf(stderr, "Removendo nodo (%d)\n", nd->key);}
    
    if (nd->left && nd->right) { // ambos os filhos existem
        return remove_both_exist(nd);
    } else {
        if (!(nd->left || nd->right)) { // nenhum filho existte
            if(DEV) {fprintf(stderr, "NENHUM EXISTE (%d), left (%d), right (%d), top (%d)\n", nd->key, nd->left ? nd->left->key : 0, nd->right ? nd->right->key : 0, nd->top ? nd->top->key : 0);}
            // atribui o esq ou dir do pai da folha para null
            if (nd->top->left == nd) { // esquerda
                nd->top->left = NULL;
            } else { // direita
                nd->top->right = NULL;
            }
            free(nd);
            return 1;
        } else { // uma das duas existe
            if(DEV) {fprintf(stderr, "Removendo nodo UMA EXISTE (%d)\n", nd->key);}
            // reatribui o ponteiro do pai para o novo filho
            if (nd->top->left == nd) { // se tem esquerdo
                nd->top->left = nd->left ? nd->left : nd->right;
            } else { // se tem direito
                nd->top->right = nd->left ? nd->left : nd->right;       
            }

            // ajusta o ponteiro do filho para o pai 
            if (nd->left) {
                nd->left->top = nd->top;
            } else {
                nd->right->top = nd->top;
            }
            free(nd);
            return 1;
        }
    }
    return 0;
}

// remove o nodo localizado no root
int remove_root(tree_t *t) {
    node_t *nd = t->root;
    if (!nd) return 0; // se nodo não existir

    if(DEV) {fprintf(stderr, "Removendo root (%d)\n", nd->key);}
    
    if (nd->left && nd->right) { // ambos os filhos existem
        return remove_both_exist(nd);
    } else {
        if (!(nd->left || nd->right)) { // nenhum filho existte
            // reinicializa a árvore
            free(nd);
            t->root = NULL;
            return 1;
        } else { // uma das duas existe
            if(DEV){fprintf(stderr, "Removendo root, uma existe nd, key: %d, left: %d, right: %d,top: %d\n", nd->key, nd->left ? nd->left->key : 0, nd->right ? nd->right->key : 0, nd->top ? nd->top->key : 0);}
            node_t *temp;
            if (nd->left) { // esquerda
                if(DEV) {fprintf(stderr, "Ajustando ESQ (%d)\n", nd->left->key);}
                temp = nd->left;
                if(nd->left->left) nd->left->left->top = nd;
                if(nd->left->right) nd->left->right->top = nd;

            } else { // direita
                if(DEV) {fprintf(stderr, "Ajustando DIR (%d)\n", nd->right->key);}
                temp = nd->right;
                if(nd->right->left) nd->right->left->top = nd;
                if(nd->right->right) nd->right->right->top = nd;
            }

            nd->key = temp->key;
            nd->left = temp->left;
            nd->right = temp->right;
            free(temp);

            return 1;
        }
    }
    return 0;
}

// busca recursivamente e remove a chave
int remove_key_by_node(node_t *nd, key_t key){
    if (!nd) return 0;

    if (nd->key == key) {
        if (DEV) {fprintf(stderr, "Removendo (pois achou) o nodo %d\n", key);}
        return remove_node(nd);
    }

    if (DEV) {fprintf(stderr, "Removendo nodo (%d)\n",key);}
    if (nd->key > key) { //esquerda
        if (DEV) {fprintf(stderr, "Removendo nodo esquerdo %d\n", nd->left ? nd->left->key : 0);}
        return remove_key_by_node(nd->left, key);
    } else { // direita
        if (DEV) {fprintf(stderr, "Removendo nodo direito %d\n", nd->right ? nd->right->key : 0);}
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
    if (DEV) {fprintf(stderr, "Buscando min(%d) e top (%d)\n", nd->key, nd->top->key);}
    if (!nd) return NULL;
    if (!nd->left) {
        if (DEV) {fprintf(stderr, "Achou min (%d), com top (%d)\n", nd->key, nd->top->key);} 
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

int last_right_node(node_t *nd){
    if (!nd->top){
        return 1;
    }
    if (nd->top->right == nd){
        return last_right_node(nd->top);
    }
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