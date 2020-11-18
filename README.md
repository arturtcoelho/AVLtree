<h1>AVLtree</h1>

<p>Este projeto foi iniciado em Novembro de 2020 para a matéria de Algoritmos e Estuturas de Dados III no período especial 2 da UFPR.</p>

<p>O intuito desse projeto é implementar uma Árvore binária do tipo AVL na linguagem C, e portar a mesma para sua utilização em Python. </p>

<h3>Arquivos:</h3>
<h4>avl_module.*</h4>
<p>Contém as funções de interface pra utilização de uma árvore AVL, contém as funçoes padrão de qualquer árvore</p>

<h4>tree_operations.*</h4>
<p>Contém as funções de apoio para a biblioteca principal:</p>

* rotate: rotaciona a árvora para balancea-la
* insert_key: insere uma chave em um nodo apontado
* remove_node: remove um nodo apontado

* As funções recursivas:
  * Busca
  * Impressão
  * Inserção
  * Remoção
  * Destruição

<h4>avl_module.c</h4>
<p>Contém a interface a ser exportada como biblioteca para utilização no código Python com ctypes</p>

<h4>avl_bridge.py</h4>
<p>Interface ponte do usuário para a árvore AVL, utilizando ctypes para importar a biblioteca implementada em C</p>
