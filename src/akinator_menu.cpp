#include "akinator_menu.h"

int menu(node_t* root, FILE* html_stream)
{
    assert(root);

    char ans = 0;
    while (ans != 'q')
    {
        menu_info();
        scanf(" %c[^\n]\n", &ans);
        clean_input_buffer();
        switch (ans)
        {
            case 'a': { find_node(root, html_stream, root); break;}
            case 'd': { give_label_def(root);   break;}
            case 'c': { compare(root);          break;}
            case 'g': { tree_dump(root, html_stream, root); break;}
            case 'r':
            {
                FILE* fp = NULL;
                choose_stream(STREAM_OUT, &fp);
                if (!fp) {fprintf(stderr, "STREAM ERROR occured before reading tree\n"); break;}

                read_tree (&root,  fp, html_stream);
                printf("akinator data was read succesfully\n");
                fclose(fp);
                break;
            }
            case 's':
            {
                FILE* fp = NULL;
                choose_stream(STREAM_OUT, &fp);
                if (!fp) {fprintf(stderr, "STREAM ERROR occured before saving tree\n"); break;}

                write_tree(root, fp, 0);
                printf("akinator data was saved succesfully\n");
                fclose(fp);
                break;
            }
            case 'q': break;

            default:
            {
                printf("Error: no such option - [%c](%d)\n", ans, ans);
                break;
            }
        }
    }

    return 0;
}

int menu_info()
{
    printf("------ MENU ------\n"
           "Choose option to execute\n"
           "[a] - akinator\n"
           "[d] - give definition for object\n"
           "[c] - compare two objects\n"
           "[r] - read akinator tree from file\n"
           "[s] - save akinator tree as file\n"
           "[g] - graph dump for akinator tree\n"
           "[q] - exit\n\n"
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
               "[q] - return\n\n"
               ">> ");

        scanf(" %c[^\n]\n", &ans);
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
                char file_name[default_str_size] = {};
                scanf("%s[^\n]\n", &file_name);
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
