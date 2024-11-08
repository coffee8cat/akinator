#include "bin_tree.h"

node_t* new_node(int key, node_t* left, node_t* right)
{
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: Calloc returned NULL in new_node()");
        return NULL;
    }
    node -> key  = key;
    node -> left  = left;
    node -> right = right;

    return node;
}

int add_node(node_t* node, int key)
{
    node_t** temp = NULL;
    if (node -> key < key) { temp = &node -> right; }
    else                   { temp = &node -> left;  }

    if (*temp) { add_node(*temp, key); }
    else
    {
        *temp = new_node(key, NULL, NULL);
        if (!*temp) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node);  return -1;}
        (*temp) -> prev = node;
    }

    return 0;
}

int print_tree(node_t* node, FILE* stream)
{
    assert(stream);

    if (!node) { return 1; }

    fprintf(stream, "{");
    if (node -> left)  { print_tree(node -> left, stream);  }
    fprintf(stream, "%d", node -> key);
    if (node -> right) { print_tree(node -> right, stream); }
    fprintf(stream, "}");

    return 0;
}

int tree_dtor(node_t* node)
{
    if (!node) { return 1; }
    if (node -> left)  { tree_dtor(node -> left);  }
    if (node -> right) { tree_dtor(node -> right); }
    free(node);

    return 0;
}
