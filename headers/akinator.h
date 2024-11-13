#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "my_stack.h"

const size_t default_str_size = 32;

struct node_t {
    int key;
    char data[default_str_size];
    node_t* left;
    node_t* right;
    node_t* parent;
};

node_t* new_node(int key, node_t* left, node_t* right, char* data);
int fix_parents(node_t* node);

int find_node(node_t* node, FILE* html_stream, node_t* root);
int get_next_node(node_t*** temp, node_t* node, char* ans);
int get_ans(char* ans);
int add_node(node_t** temp);

int give_label_def(node_t* root);
int compare(node_t* root);
int print_similar_features(node_t** node, stack_t* path_stack1, stack_t* path_stack2);
int print_features(node_t* node, stack_t* path_stack);

int get_path(node_t* node, stack_t* path_stack);
node_t* node_label_search(node_t* node, char* label);
int print_label_def(node_t* node, stack_t* path_stack, char label[default_str_size]);

int read_tree(node_t** node, FILE* stream, FILE* html_stream);
int write_tree(node_t* node, FILE* stream, int depth);
int print_tree(node_t* node, FILE* stream);

int tree_dtor(node_t* node);

inline void clean_input_buffer()
{
    while (getchar() != '\n')
        continue;
}

#endif
