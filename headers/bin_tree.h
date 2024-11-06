#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node_t {
    int data;
    node_t* left;
    node_t* right;
};


node_t* new_node(int data, node_t* left, node_t* right);
int add_node(node_t* node, int data);

int print_tree(node_t* node);

#endif
