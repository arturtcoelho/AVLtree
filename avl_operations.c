#include <stdlib.h>
#include <stdio.h>

#include "avl_module.h"
#include "tree_operations.h"
#include "avl_operations.h"

uint8_t balance_factor(node_t *nd){
    if (!nd) return 0;
    uint8_t left_height = height_by_node(nd->left, 0);
    uint8_t right_height = height_by_node(nd->right, 0);
    return right_height - left_height;
}