#ifndef __AVL_TREE__
#define __AVL_TREE__

// definição da macro DEV, para uso de debug
#if defined DEBUG
	#define DEV 1
#else
	#define DEV 0
#endif

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
	int height;
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

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_avl(avl_t *t, key_t key);

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_avl(avl_t *t);

#endif