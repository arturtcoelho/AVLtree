## My AVL tree
[GitHub](https://github.com/arturtemporal/AVLtree)

**Autores:** Artur Temporal Coelho & Gabriel Nascarella Hishida do Nascimento

**Sobre:** Este trabalho foi realizado para a matéria Algoritmos e estrutura de dados III, ERE 2 2020, durante o mês de novembro. Consiste de uma biblioteca de uma árvore binária AVL construida em C e importada para um módulo Python para sua utilização abstraida.

## `myavl.py`
O arquivo myavl.py importa o módulo avl_bridge e provém uma interface com uma árvore AVL para o usuário, com suas funções de leitura e impressão na tela.

## `avl_bridge.py`
A ponte AVL utiliza o módulo ctypes para fazer a interface entre o programa myavl e a biblioteca avl_module. As funções que estão disponiveis para uso, seu nome em avl_module e seu método correspondente em avl_bridge são:

 - `initialize_avl(avl_t)` -> `__init__`: construtor da árvore
 - `insert_key_avl(avl_t, key_t)` -> `insert_key(int)`: insere a chave na árvore
 - `search_key_avl(avl_t)` -> `search_key(int)`: retorna 1 caso a chave esteja presente na árvore, 0 caso não exista
 - `remove_key_avl(avl_t)` -> `remove_key(int)`: remove a chave da árvore
 - `print_tree_avl(avl_t)` -> `print_tree()`: imprime a árvore in-order 
 - `print_parenthesis(avl_t)` -> `print_tree_parenthesis()`: imprime a árvore na notação de parenteses
 - `print_with_height(avl_t)` -> `print_with_height()`: imprime a árvore in-order, com a altura de cada nodo 
 - `print_graph(avl_t)` -> `print_graph()`: imprime a árvore de forma gráfica, a partir da esquerda 
 - `string_parenthesis(avl_t)` -> `as_parenthesis_string()`: retorna uma string com a notação de parenteses
 - `string_with_height(avl_t)` -> `as_height_string()`: retorna uma string com a árvore in-order com altura
 - `tree_size(avl_t)` -> `size()`: retorna o número de nodos na árvore
 - `tree_height(avl_t)` -> `height()`: retorna a altura da aŕvore 
 - `destroy_tree_avl(avl_t)` -> `__del__`: destrutor da classe, removendo todos os nodos


## `avl_module.so`
Este é o arquivo utilizado pela ponte para realizar as operações com a árvore, este é o arquivo montado pelo Makefile, dependendo das seguintes implementações:

 - **avl_module:** Contém as definições de tipos e as funções de interface visiveis pela ponte
 - **tree_operations:** Contém as implementações recursivas principais de busca, inserção e remoção
 - **avl_operations:**  Contém as implementações das funções específicas de uma árvore AVL, como rotação e ajuste do fator de balanceamento
 - **print_tree:** Contém as diversas funções de impressão da árvore
 
## `Makefile`
O Makefile foi construido com os alvos:
 - `all`, para compilação e montagem dos arquivos objetos culminando no objeto compartilhado avl_module.so
 -  `clean`, para remoção dos arquivos objeto 
 - `purge`, para remoção de todos os arquivos que não sejam código fonte
 - `install`, para instalação da biblioteca para uso geral na maquina
