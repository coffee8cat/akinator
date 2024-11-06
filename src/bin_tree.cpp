#include "bin_tree.h"

node_t* new_node(int data, node_t* left, node_t* right)
{
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: Calloc returned NULL in new_node()");
        return NULL;
    }
    node -> data  = data;
    node -> left  = left;
    node -> right = right;

    return node;
}

int add_node(node_t* node, int data)
{
    if (node -> data < data)
    {
        if (node -> right) { add_node(node -> right, data); }
        else
        {
            node -> right = new_node(data, NULL, NULL);
            if (!node -> right) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node); }
        }
    }
    else
    {
        if (node -> left) { add_node(node -> left, data); }
        else
        {
            node -> left = new_node(data, NULL, NULL);
            if (!node -> left) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node); }
        }
    }

    return 0;
}

FILE* prepare_to_dump()
{
    system("make clean_data\n");
    FILE* fp = fopen("list_dump.html", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open html file fot dump\n");
        return NULL;
    }
    fprintf(fp, "<pre>\n");

    return fp;
}

int tree_dump(node_t* root, FILE* html_stream)
{
    static size_t dump_counter = 1;
    char dot_file_name[BUFSIZ] = "";
    char png_file_name[BUFSIZ] = "";
    sprintf(dot_file_name, "data\\dump%d.dot", dump_counter);
    sprintf(png_file_name, "data\\dump%d.png", dump_counter);

    FILE* fp = fopen(dot_file_name, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: Unable to open file for dump\n");
        return -1;
    }

    make_dot_file(root, fp);
    fclose(fp);

    char command[BUFSIZ] = "";
    sprintf(command, "dot %s -Tpng -o %s\n", dot_file_name, png_file_name);
    system(command);

    dump_to_html(root, png_file_name, html_stream);

    dump_counter++;
    return 0;
}

int dump_to_html(node_t* root, char* png_file_name, FILE* html_stream)
{
    assert(root);
    assert(png_file_name);

    fprintf(html_stream, "MEMORY PRINT\n");
    print_tree(root, html_stream);

    fprintf(html_stream, "\n<img src=%s>\n", png_file_name);

    return 0;
}

int make_dot_file(node_t* root, FILE* fp)
{
    assert(fp);
    assert(root);

    fprintf(fp, "digraph\n{\n"
                "    rankdir=TP\n\n"
                "    ");

    write_node_info(root, fp);

    fprintf(fp, "}");

    printf("dot file completed\n");
    return 0;
}

int write_node_info(node_t* node, FILE* fp)
{
    assert(fp);

    if (!node) { return 1; }

    fprintf(fp, "    node%p[shape=record,style=\"rounded,filled\",fillcolor=\"#39CCCC\",label=\"{ ptr: %p | data: %d | { left: %p | right: %p }}\"];\n",
            node, node, node -> data, node -> left, node -> right);

    if (node -> left)
    {
        fprintf(fp, "    node%p -> node%p[color=\"#0855F0\"]\n", node, node -> left);
        write_node_info(node -> left, fp);
    }
    if (node -> right)
    {
        fprintf(fp, "    node%p -> node%p[color=\"#0855F0\"]\n", node, node -> right);
        write_node_info(node -> right, fp);
    }

    return 0;
}

int print_tree(node_t* node, FILE* stream)
{
    assert(stream);

    if (!node) { return 1; }

    fprintf(stream, "{");
    if (node -> left)  { print_tree(node -> left, stream);  }
    fprintf(stream, "%d", node -> data);
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
