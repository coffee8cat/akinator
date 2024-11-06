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

FILE* prepare_to_dump();
int tree_dump(node_t* root, FILE* html_stream);
int dump_to_html(node_t* root, char* png_file_name, FILE* html_stream);
int make_dot_file(node_t* root, FILE* fp);
int write_node_info(node_t* node, FILE* fp);
int print_tree(node_t* node, FILE* stream);

int tree_dtor(node_t* node);

#endif
