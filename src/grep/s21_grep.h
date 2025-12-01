#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char* pattern;
  size_t pattern_len;
  size_t pattern_mem;
} arguments;

void pattern_add(arguments* arg, char* pattern);
void add_reg_from_file(arguments* arg, char* filepath);
arguments arguments_parser(int argc, char* argv[]);
void output_line(char* line, int n);
void match_line(char* line, regex_t* reg);
void process_file(arguments arg, char* path, regex_t* reg);
void output(arguments arg, int argc, char** argv);

#endif