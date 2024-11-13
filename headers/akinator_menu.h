#ifndef _AKINATOR_MENU_H__
#define _AKINATOR_MENU_H__

#include "akinator.h"

const char  default_in_stream[32] = "data\\tree1.txt";
const char default_out_stream[32] = "data\\tree1_saved.txt";

enum {STREAM_IN, STREAM_OUT};

int menu(node_t* root, FILE* stream_in, FILE* stream_out, FILE* html_stream);
int menu_info();
int choose_stream(int mode, FILE** fp);

#endif