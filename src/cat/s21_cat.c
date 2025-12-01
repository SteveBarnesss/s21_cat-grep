#include "s21_cat.h"

arguments argument_parser(int argc, char** argv) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      case '?':
        perror("ERROR");
        exit(1);
        break;
      default:
        break;
    }
  }
  return arg;
}

char v_print(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch > 0 && ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(arguments* arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t')
      printf("^I");
    else {
      if (arg->E && line[i] == '\n') {
        putchar('$');
      }
      if (arg->v) line[i] = v_print(line[i]);
      putchar(line[i]);
    }
  }
}

void read_stdin() {
  FILE* f = stdin;
  char* line = NULL;
  size_t memline = 0;
  int read;
  while ((read = getline(&line, &memline, f)) != -1) {
    fwrite(line, 1, read, stdout);
  }
  free(line);
}

void read_file(arguments* arg, int argc, char* argv[]) {
  if (optind == argc) {
    read_stdin();
  } else {
    for (int i = optind; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      if (!f) {
        perror("Error opening file");
        return;
      }
      char* line = NULL;
      size_t memline = 0;
      int read = 0;
      int line_count = 1;
      int empty_count = 0;
      read = getline(&line, &memline, f);

      while (read != -1) {
        if (line[0] == '\n')
          empty_count++;
        else
          empty_count = 0;
        if (!(arg->s && empty_count > 1)) {
          if (arg->b) {
            if (line[0] != '\n') {
              printf("%6d\t", line_count);
              line_count++;
            } else if (arg->E) {
              printf("%6s\t", "");
            }
          } else if (arg->n) {
            printf("%6d\t", line_count);
            line_count++;
          }
          outline(arg, line, read);
        }
        read = getline(&line, &memline, f);
      }
      free(line);
      fclose(f);
    }
  }
}

int main(int argc, char* argv[]) {
  arguments arg = argument_parser(argc, argv);
  read_file(&arg, argc, argv);
  return 0;
}