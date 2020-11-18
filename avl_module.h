#ifndef AVL_MODULE
#define AVL_MODULE

// definição da macro DEV, para uso de debug
#if defined DEBUG
	#define DEV 1
#else
	#define DEV 0
#endif

#define MAX_NUM_LEN 4

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
int _initialize_avl(avl_t *t);

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int _insert_key_avl(avl_t *t, key_t key);

// procura uma chave key na árvore, retorna 0 em caso de erro e !0 caso contrário
int _search_key_avl(avl_t *t, key_t key);

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int _print_tree_avl(avl_t *t);
int _print_parethesis(avl_t *t);
int _print_with_height(avl_t *t);

// escreve em str a árvore em notação de parenteses, retorna o número de caracteres escritos
int _string_parenthesis(avl_t *t, char *str, int max);

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int _remove_key_avl(avl_t *t, key_t key);

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int _destroy_tree_avl(avl_t *t);

int _tree_size(avl_t *t);

int _tree_height(avl_t *t);

#endif