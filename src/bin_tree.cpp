#include "bin_tree.h"
#include "tree_dump.h"

node_t* new_node(int key, node_t* left, node_t* right, char* data)
{
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: Calloc returned NULL in new_node()");
        return NULL;
    }
    node -> key   = key;
    node -> left  = left;
    node -> right = right;
    strcpy(node -> data, data);

    return node;
}

int fix_parents(node_t* node)
{
    assert(node);
    if (node -> right) {(node -> right) -> parent = node;}
    if (node -> left)  {(node -> left) ->  parent = node;}

    return 0;
}

int find_node(node_t* node, FILE* html_stream)
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

    printf("temp: %p\n", *temp);

    if (*temp)
    {
        if ((*temp) -> left == NULL && ((*temp) -> right) == NULL)
        {
            printf("It is %s, right?\n", (*temp) -> data);
            while (true)
            {
                fscanf(stdin, "%c", &ans);
                clean_input_buff();
                if (!(ans == 'Y' || ans == 'N'))
                    printf("Unknown symbol: %c(%d)\nOnly Y and N are accepted as answers\n", ans, ans);
                else
                    break;
            }
            if (ans == 'N')
            {
                //change_and_add_node()
                printf("What was it?\n");
                char new_label[32] = {};
                scanf("%s", new_label);

                printf("what is the difference between %s and %s?(Enter the question)\n"
                       "(True for %s, false for %s)\n",
                       new_label, (*temp) -> data, new_label, (*temp) -> data);

                char question[32] = {};
                scanf("%s", question);

                node_t* question_node = new_node(0, NULL, NULL, question);
                node_t* label_node    = new_node(0, NULL, NULL, new_label);

                question_node -> right = label_node;
                question_node -> left  = *temp;

                node_t* parent = (*temp) -> parent;

                *temp = question_node;

                fix_parents(parent);
                fix_parents(question_node);

                tree_dump(node, html_stream, node);
            }
            return 0;
        }
        else
        {
            find_node(*temp, html_stream);
            return 0;
        }
    }
    else
    {
        printf("No such item yet\n"
               "What is it?\n");
        *temp = new_node(0, NULL, NULL, "");
        if (!*temp) { fprintf(stderr, "ERROR: ADDITION FIALED on node [%p]\n", node);  return -1;}
        (*temp) -> parent = node;
    }

    return -1;
}

int give_label_def(node_t* root)
{
    assert(root);

    char label[32] = {};
    scanf("%s", label);
    node_t* node = node_label_search(root, label);

    printf("label found: %p\n", node);
    stack_t path_stack = {};
    stack_init(&path_stack, 16, sizeof(stack_elem_t));

    while (node -> parent)
    {
        if ((node -> parent) -> right == node) {stack_push(&path_stack, 1);}
        else if ((node -> parent) -> left == node) {stack_push(&path_stack, 0);}

        node = node -> parent;
    }

    STACK_DUMP(&path_stack, __func__);

    size_t path_length = path_stack.size;

    printf("Definition of %s:\n", label);
    for (size_t i = 0; i < path_length; i++)
    {
        int direction = 0;
        stack_pop(&path_stack, &direction);
        if (direction == 1)
        {
            printf("    %s\n", node -> data);
            node = node -> right;
        }
        else
        {
            printf("Not %s\n", node -> data);
            node = node -> left;
        }
    }

    return 0;
}

node_t* node_label_search(node_t* node, char* label)
{
    assert(node);
    assert(label);

    if (strcmp(node -> data, label) == 0) {return node;}
    else
    {
        node_t* ans = NULL;
        if (node -> right && (ans = node_label_search(node -> right, label)))
        {
            printf("label to return: %p", ans);
            return ans;
        }
        if (node -> left && (ans = node_label_search(node -> left, label)))
        {
            printf("label to return: %p", ans);
            return ans;
        }
    }

    return NULL;
}

int read_tree(node_t** node, FILE* stream, FILE* html_stream)
{
    assert(stream);
    char ch = 0;
    fscanf(stream, " %c", &ch);
    printf("ch: %c\nnode : %p\n", ch, *node);
    switch (ch)
    {
        case '{':
        {
            char label[32] = {};
            fscanf(stream, " \"%[^\"]\"", label);
            printf("%s\n", label);
            *node = new_node(0, NULL, NULL, label);
            read_tree(node, stream, html_stream);
            break;
        }
        case 'y':
        {
            char temp = 0;
            while(temp != '{')
                fscanf(stream, "%c", &temp);

            char label[32] = {};
            fscanf(stream, " \"%[^\"]\"", label);
            printf("%s\n", label);
            (*node) -> right = new_node(0, NULL, NULL, label);
            ((*node) -> right) -> parent = *node;

            read_tree(&((*node) -> right), stream, html_stream);
        }
        case 'n':
        {
            char temp = 0;
            while(temp != '{')
                fscanf(stream, "%c", &temp);

            char label[32] = {};
            fscanf(stream, " \"%[^\"]\"", label);
            printf("%s\n", label);
            (*node) -> left = new_node(0, NULL, NULL, label);
            ((*node) -> left) -> parent = *node;

            read_tree(&((*node) -> left), stream, html_stream);
            break;
        }
        case '}': {return 0;}
        default:{fprintf(stderr, "Unknown option: %c\n", ch); break;}
    }


    tree_dump(*node, html_stream, *node);
    print_tree(*node, stdout);
    return 0;
}

int print_tree(node_t* node, FILE* stream)
{
    assert(stream);

    if (!node) { return 1; }

    fprintf(stream, "{");
    fprintf(stream, "%s", node -> data);
    if (node -> left)  { print_tree(node -> left, stream);  }
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
