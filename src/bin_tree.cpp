#include "bin_tree.h"

node_t* new_node(int data, node_t* left, node_t* right)
{
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: Calloc returned NULL in new_node()");
        return NULL;
    }
    node -> data  = data;
    node -> left  = left;
    node -> right = right;

    return node;
}

int add_node(node_t* node, int data)
{
    if (node -> data < data)
    {
        if (node -> right) { add_node(node -> right, data); }
        else
        {
            node -> right = new_node(data, NULL, NULL);
            if (!node -> right) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node); }
        }
    }
    else
    {
        if (node -> left) { add_node(node -> left, data); }
        else
        {
            node -> left = new_node(data, NULL, NULL);
            if (!node -> left) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node); }
        }
    }

    return 0;
}

int print_tree(node_t* node)
{
    if (!node) { return 1; }

    printf("{");
    if (node -> left) { print_tree(node -> left); }
    printf("%d", node -> data);
    if (node -> right) { print_tree(node -> right); }
    printf("}");

    return 0;
}
