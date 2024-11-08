#include "bin_tree.h"
#include "tree_dump.h"

int main()
{
    FILE* html_stream = prepare_to_dump();
    if (html_stream == NULL)
        return -1;

    node_t* root = new_node(0, NULL, NULL);
    if (!root) {return -1;}
    printf("got here\n");
    root -> right = new_node(0, NULL, NULL);
    root -> left  = new_node(0, NULL, NULL);

    printf("got here\n");
    (root -> right) -> left = new_node(0, NULL, NULL);

    tree_dump(root, html_stream, root);
    find_node(root);

    tree_dump(root, html_stream, root);

    tree_dtor(root);

    return 0;
}
