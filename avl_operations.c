#include <stdlib.h>
#include <stdio.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"

int balance_factor(node_t *nd){
    if (!nd) return 0;
    int left_height = height_by_node(nd->left, 0);
    int right_height = height_by_node(nd->right, 0);
    return right_height - left_height;
}