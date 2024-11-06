#include "bin_tree.h"

int main()
{
    node_t* root = new_node(50, NULL, NULL);
    if (!root) {return -1;}
    add_node(root, 30);
    add_node(root, 70);
    add_node(root, 40);

    print_tree(root);

    return 0;
}
