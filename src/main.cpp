#include "bin_tree.h"
#include "tree_dump.h"

int main()
{
    FILE* html_stream = prepare_to_dump();
    if (html_stream == NULL)
        return -1;

    node_t* root = new_node(0, NULL, NULL, "root");
    if (!root) {return -1;}

    FILE* fp = fopen("data\\tree1.txt", "r");
    read_tree(&root, fp, html_stream);

    tree_dump(root, html_stream, root);

    //find_node(root, html_stream);
    give_label_def(root);
    tree_dtor(root);

    return 0;
}
