## My AVL tree

**Autores:** Artur Temporal Coelho & Gabriel Nascarella Hishida do Nascimento

**Sobre:** Este trabalho foi realizado para a matéria Algoritmos e estrutura de dados III, ERE 2 2020, durante o mês de novembro. Consiste de uma biblioteca de uma árvore binária AVL construida em C e importada por um módulo Python para sua utilização abstraida.

## myavl .py
O arquivo myavl .py importa o módulo avl e contém a interface com a árvore, sua função de leitura e impressão na tela para o usuário.

## avl_bridge .py
A ponte AVL utiliza a biblioteca ctypes para fazer a interface entre o programa myavl e a biblioteca avl_module

## avl_module .so
Este é o arquivo utilizado pela ponte para realizar as operações com a árvore, este é o arquivo montado pelo Makefile, dependendo das seguintes implementações:

 - **avl_module:** Contém as definições de tipos e as funções de interface visiveis pela ponte
 - **tree_operations:** Contém as implementações recursivas principais de busca, inserção e remoção
 - **avl_operations:**  Contém as implementações das funções específicas de uma árvore AVL, como rotação e ajuste do fator de balanceamento
 - **print_tree:** Contém as diversas funções de impressão da árvore
## Makefile
O Makefile foi construido com os alvos:
 - `all`, para compilação e montagem dos arquivos objetos culminando no objeto compartilhado avl_module.so
 -  `clean`, para remoção dos arquivos objeto 
 - `purge`, para remoção de todos os arquivos que não sejam código fonte
 - `install`, para instalação da biblioteca para uso geral na maquina
