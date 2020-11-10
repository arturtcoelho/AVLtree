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

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 ao contrário
int initialize_avl(avl_t *t);

// adiciona uma chave key_t na árvore, retorna 0 em caso de erro e !0 ao contrário
int add_key_avl(avl_t *t, key_t key);

// procura uma chave na árvore e insere seu valor em key, retorna 0 em caso de erro e !0 ao contrário
int find_key_avl(avl_t *t, key_t *key);

// imprime a árvore na saída padrão, retorna 0 em caso de erro e !0 ao contrário
int print_tree_avl(avl_t *t);

// remove uma chave da árvore, retorna 0 em caso de erro e !0 ao contrário
int delete_key_avl(avl_t *t, key_t key);

// destroi a árvore, retorna 0 em caso de erro e !0 ao contrário
int remove_tree_avl(avl_t *t);

#endif