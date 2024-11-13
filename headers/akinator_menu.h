#ifndef _AKINATOR_MENU_H__
#define _AKINATOR_MENU_H__

#include "akinator.h"

const char  default_in_stream[default_str_size] = "data\\tree1.txt";
const char default_out_stream[default_str_size] = "data\\tree1_saved.txt";

enum {STREAM_IN, STREAM_OUT};

int menu(node_t* root, FILE* html_stream);
int menu_info();
int choose_stream(int mode, FILE** fp);

#endif
