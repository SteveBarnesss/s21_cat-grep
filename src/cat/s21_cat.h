#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, n, s, e, E, t, T, v;
} arguments;

struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                {"number-nonblank", no_argument, NULL, 'b'},
                                {"squeeze-blank", no_argument, NULL, 's'},
                                {0, 0, 0, 0}};

arguments argument_parser(int argc, char** argv);
char v_print(char ch);
void outline(arguments* arg, char* line, int n);
void read_stdin();
void read_file(arguments* arg, int argc, char* argv[]);

#endif