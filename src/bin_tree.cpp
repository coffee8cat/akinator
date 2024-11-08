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

    scanf("%s", node -> data);

    return node;
}

int find_node(node_t* node)
{
    fprintf(stdout, "%s?\n", node -> data);

    char ans = 0;

    node_t** temp = NULL;
    while (true)
    {
        fscanf(stdin, "%c", &ans);
        clean_input_buff();
        if      (ans == 'Y') { temp = &node -> right; break; }
        else if (ans == 'N') { temp = &node -> left;  break; }
        else {printf("Unknown symbol: %c(%d)\nOnly Y and N are accepted as answers\n", ans, ans);}
    }

    printf("temp: %p", *temp);

    /*if ((*temp) -> left == NULL && ((*temp) -> right) == NULL)
    {
        printf("It is %s, right?\n", (*temp) -> data);
        return 0;
    }*/
    if (*temp) { find_node(*temp); }
    else
    {
        printf("No such item yet\n"
               "What is it?\n");
        *temp = new_node(0, NULL, NULL);
        if (!*temp) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node);  return -1;}
        (*temp) -> prev = node;
    }

    return -1;
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
