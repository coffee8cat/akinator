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
            case 'r':
            {
                FILE* fp = NULL;
                choose_stream(STREAM_OUT, &fp);
                if (!fp) {fprintf(stderr, "STREAM ERROR occured before reading tree\n"); break;}

                read_tree (&root,  fp, html_stream);
                fclose(fp);
                break;
            }
            case 's':
            {
                FILE* fp = NULL;
                choose_stream(STREAM_OUT, &fp);
                if (!fp) {fprintf(stderr, "STREAM ERROR occured before saving tree\n"); break;}

                write_tree(root, fp, 0);
                fclose(fp);
                break;
            }
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

int choose_stream(int mode, FILE** fp)
{
    char ans = 0;
    while (ans != 'q')
    {
        printf("Choose stream:\n"
               "[d] - default stream\n"
               "[c] - write a path to file for stream\n"
               "[q] - return\n");
        scanf(" %c[^\n]", &ans);
        switch (ans)
        {
            case 'd':
            {
                if (mode == STREAM_OUT) { *fp = fopen(default_out_stream, "w");}
                if (mode == STREAM_IN)  { *fp = fopen(default_in_stream,  "r");}

                ans = 'q'; break;
            }
            case 'c':
            {
                printf("Enter path: ");
                char file_name[32] = {};
                if (mode == STREAM_OUT) { *fp = fopen(file_name, "w");}
                if (mode == STREAM_IN)  { *fp = fopen(file_name, "r");}

                ans = 'q'; break;
            }
            case 'q': break;

            default: printf("Error: no such option - [%c](%d)\n", ans, ans);
                    break;
        }
    }
    if (*fp) { return 0; }
    else     { return -1;}
}
