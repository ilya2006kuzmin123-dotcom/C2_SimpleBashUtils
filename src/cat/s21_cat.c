#include "s21_cat.h"

void print_formatted_char(int current_char, struct CatFlags flags) {
  if ((flags.e == 1 || flags.E == 1) && current_char == '\n') putchar('$');
  if ((flags.t == 1 || flags.T == 1) && current_char == '\t')
    printf("^I");
  else if (flags.v == 1 && current_char != '\n' && current_char != '\t') {
    if (current_char < 32)
      printf("^%c", current_char + 64);
    else if (current_char == 127)
      printf("^?");
    else
      putchar(current_char);
  } else
    putchar(current_char);
}

void read(const char* filename, struct CatFlags flags, int* cnt) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "No");
  } else {
    int current_char;
    int is_new_line = 1;
    int null_lines_cnt = 0;
    while ((current_char = fgetc(file)) != EOF) {
      int need_to_print = 1;
      if (is_new_line == 1 && current_char == '\n')
        null_lines_cnt++;
      else if (current_char != '\n')
        null_lines_cnt = 0;
      if (flags.s == 1 && is_new_line == 1 && null_lines_cnt > 1)
        need_to_print = 0;
      if (need_to_print == 1) {
        if (is_new_line == 1) {
          if (flags.b == 1 && current_char != '\n')
            printf("%6d\t", (*cnt)++);
          else if (flags.n == 1)
            printf("%6d\t", (*cnt)++);
        }
        print_formatted_char(current_char, flags);
      }
      is_new_line = (current_char == '\n') ? 1 : 0;
    }
    fclose(file);
  }
}

int main(int argc, char* argv[]) {
  struct CatFlags flags = {0};
  int cnt = 1;
  int opt;
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, "benstTvE", long_options, NULL)) !=
         -1) {
    if (opt == 'b') {
      flags.b = 1;
      flags.n = 0;
    } else if (opt == 'e') {
      flags.e = 1;
      flags.v = 1;
    } else if (opt == 'n') {
      if (flags.b == 0) flags.n = 1;
    } else if (opt == 's')
      flags.s = 1;
    else if (opt == 't') {
      flags.t = 1;
      flags.v = 1;
    } else if (opt == 'v')
      flags.v = 1;
    else if (opt == 'E')
      flags.E = 1;
    else if (opt == 'T')
      flags.T = 1;
  }
  for (int i = optind; i < argc; i++) {
    read(argv[i], flags, &cnt);
  }
  return 0;
}