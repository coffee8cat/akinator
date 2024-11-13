#include "akinator_menu.h"

int menu(node_t* root, FILE* stream_in, FILE* stream_out, FILE* html_stream)
{
    assert(root);

    char ans = 0;
    while (ans != 'q')
    {
        menu_info();
        scanf(" %c[^\n]", &ans);
        switch (ans)
        {
            case 'a': { find_node(root, html_stream); break;}
            case 'd': { give_label_def(root);   break;}
            case 'c': { compare(root);          break;}
            case 'r': { read_tree (&root,  stream_in, html_stream); break;}
            case 's': { write_tree(root,   stream_out, 0); break;}
            case 'q': break;

            default: printf("Error: no such option - [%c](%d)\n", ans, ans);
                    break;
        }
    }

    return 0;
}

int menu_info()
{
    printf("--- MENU ---\n"
           "Choose option to execute\n"
           "[a] - akinator\n"
           "[d] - give definition for object\n"
           "[c] - compare two objects\n"
           "[r] - read akinator tree from file\n"
           "[s] - save akinator tree as file\n"
           "[q] - exit\n"
           ">> ");
}
