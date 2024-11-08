#include "bin_tree.h"
#include "tree_dump.h"

int main()
{
    FILE* html_stream = prepare_to_dump();
    if (html_stream == NULL)
        return -1;

    node_t* root = new_node(50, NULL, NULL);
    if (!root) {return -1;}
    add_node(root, 30);
    add_node(root, 70);
    add_node(root, 40);

    print_tree(root, stdout);
    tree_dump(root, html_stream, root);
    add_node(root, 12);
    tree_dump(root, html_stream, root);

    tree_dtor(root);

    return 0;
}
