#ifndef AVL_MODULE
#define AVL_MODULE

// definição da macro DEV, para uso de debug
#if defined DEBUG
	#define DEV 1
#else
	#define DEV 0
#endif

#define MAX_NUM_LEN 4
#define SPACING 5

typedef int key_t;

struct node {
	key_t key;
	struct node *top;
	struct node *left;
	struct node *right;
};
typedef struct node node_t;

struct avl {
	node_t *root;
};
typedef struct avl avl_t;

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
int initialize_avl(avl_t *t);

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int insert_key_avl(avl_t *t, key_t key);

// procura uma chave key na árvore, retorna 0 em caso de erro e !0 caso contrário
int search_key_avl(avl_t *t, key_t key);

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int print_tree_avl(avl_t *t);
int print_parethesis(avl_t *t);
int print_with_height(avl_t *t);
int print_graph(avl_t *t);

// escreve em str a árvore, retorna o número de caracteres escritos
int string_parenthesis(avl_t *t, char *str, int max);
int string_height(avl_t *t, char * str, int max);

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_avl(avl_t *t, key_t key);

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_avl(avl_t *t);

int tree_size(avl_t *t);

int tree_height(avl_t *t);

#endif