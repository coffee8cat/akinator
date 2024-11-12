#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node_t {
    int key;
    char data[32];
    node_t* left;
    node_t* right;
    node_t* parent;
};


node_t* new_node(int key, node_t* left, node_t* right, char* data);\
int fix_parents(node_t* node);
int find_node(node_t* node, FILE* html_stream);

int read_tree(node_t** node, FILE* stream, FILE* html_stream);
int print_tree(node_t* node, FILE* stream);

int tree_dtor(node_t* node);

inline void clean_input_buff()
{
    while (getchar() != '\n')
        continue;
}

#endif
