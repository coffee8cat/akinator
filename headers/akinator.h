#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "my_stack.h"

struct node_t {
    int key;
    char data[32];
    node_t* left;
    node_t* right;
    node_t* parent;
};


node_t* new_node(int key, node_t* left, node_t* right, char* data);
int fix_parents(node_t* node);
int find_node(node_t* node, FILE* html_stream);

int give_label_def(node_t* root);
int compare(node_t* root);

int get_path(node_t* node, stack_t* path_stack);
node_t* node_label_search(node_t* node, char* label);
int print_label_def(node_t* node, stack_t* path_stack, char label[32]);

int read_tree(node_t** node, FILE* stream, FILE* html_stream);
int print_tree(node_t* node, FILE* stream);

int tree_dtor(node_t* node);

inline void clean_input_buff()
{
    while (getchar() != '\n')
        continue;
}

#endif
