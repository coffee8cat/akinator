#include "akinator.h"
#include "akinator_menu.h"
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
    fclose(fp);

    menu(root, fp, fpout, html_stream);

    tree_dtor(root);
    fclose(html_stream);

    return 0;
}
