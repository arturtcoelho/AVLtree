#ifndef tree_module
#define tree_module

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

struct tree {
	node_t *root;
};
typedef struct tree tree_t;

// inicializa a árvore, necessário para iniciar operações, retorna 0 em caso de erro e !0 caso contrário
int initialize_tree(tree_t *t);

// insere uma chave key_t na árvore, retorna 0 em caso de erro e !0 caso contrário
int insert_key_tree(tree_t *t, key_t key);

// procura uma chave key na árvore, retorna 0 em caso de erro e !0 caso contrário
int search_key_tree(tree_t *t, key_t key);

// imprime a árvore in-order na saída padrão, retorna 0 em caso de erro e !0 caso contrário
int print_tree_tree(tree_t *t);
int print_parethesis(tree_t *t);
int print_with_height(tree_t *t);
int print_graph(tree_t *t);

// escreve em str a árvore, retorna o número de caracteres escritos
int string_parenthesis(tree_t *t, char *str, int max);
int string_height(tree_t *t, char * str, int max);

// remove uma chave da árvore, retorna 0 em caso de erro e !0 caso contrário
int remove_key_tree(tree_t *t, key_t key);

// destroi a árvore, retorna 0 em caso de erro e !0 caso contrário
int destroy_tree_tree(tree_t *t);

int tree_size(tree_t *t);

int tree_height(tree_t *t);

#endif