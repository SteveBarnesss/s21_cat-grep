#include "s21_grep.h"

void pattern_add(arguments* arg, char* pattern) {
  size_t pattern_size = strlen(pattern);
  if (arg->pattern_len == 0) {
    arg->pattern_mem = 1024;
    arg->pattern = malloc(arg->pattern_mem);
    if (arg->pattern == NULL) {
      perror("malloc");
      exit(1);
    }
    arg->pattern[0] = '\0';
  }
  // | + '\0' = 2
  size_t needed = arg->pattern_len + pattern_size + 2;
  if (needed > arg->pattern_mem) {
    arg->pattern_mem *= 2;
    if (arg->pattern_mem < needed) arg->pattern_mem = needed;

    char* new_pattern = realloc(arg->pattern, arg->pattern_mem);
    if (new_pattern == NULL) {
      perror("realloc");
      free(arg->pattern);
      exit(1);
    }
    arg->pattern = new_pattern;
  }

  if (arg->pattern_len > 0) {
    strcat(arg->pattern, "|");  // Используем strcat к самому буферу
    arg->pattern_len++;
  }
  strcat(arg->pattern, pattern);
  arg->pattern_len += pattern_size;
}

void add_reg_from_file(arguments* arg, char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = getline(&line, &memlen, f);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_add(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

arguments arguments_parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.pattern_len == 0) {
    if (optind >= argc) {
      fprintf(stderr, "usage: grep [OPTION]... PATTERN [FILE]...\n");
      exit(1);
    }
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void match_line(char* line, regex_t* reg) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(reg, line + offset, 1, &match, 0);
    if (result != 0) {
      return;
    }
    // Защита от бесконечного цикла
    // Если найдено совпадение длины 0 (пустая строка)
    if (match.rm_eo == match.rm_so) {
      offset++;  // Принудительно сдвигаемся на 1 символ
      continue;  // Пропускаем печать (пустое совпадение все равно нечего
                 // печатать)
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar((line + offset)[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void process_file(arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    return;
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_number = 1;
  int lines_match = 0;
  read = getline(&line, &memlen, f);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      lines_match++;
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_number);
        if (arg.o && !arg.v) {
          match_line(line, reg);
        } else {
          output_line(line, read);
        }
      }
    }
    read = getline(&line, &memlen, f);
    line_number++;
  }
  if (arg.l && lines_match > 0) {
    printf("%s\n", path);
  } else if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", lines_match);
  }
  free(line);
  fclose(f);
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    perror("regcomp");
    return;
  }
  for (int i = optind; i < argc; i++) {
    process_file(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char** argv) {
  arguments arg = arguments_parser(argc, argv);
  output(arg, argc, argv);
  free(arg.pattern);
  return 0;
}