#include "s21_grep.h"

#include "../common/s21_common.h"

void print_only_matching(const char* filename, struct GrepFlags flags,
                         int line_cnt, int is_several, regex_t* regex,
                         char* line) {
  regmatch_t pmatch;
  char* shift_line = line;
  while (regexec(regex, shift_line, 1, &pmatch, 0) == 0) {
    if (is_several == 1 && flags.h == 0) printf("%s:", filename);
    if (flags.n == 1) printf("%d:", line_cnt);
    for (int i = pmatch.rm_so; i < pmatch.rm_eo; i++) {
      putchar(shift_line[i]);
    }
    putchar('\n');
    shift_line += pmatch.rm_eo;
  }
}

int match_file_patterns(const char* line, const char* patterns_file,
                        struct GrepFlags flags) {
  FILE* pf = fopen(patterns_file, "r");
  int is_match = 0;
  if (pf != NULL) {
    char* p_line = NULL;
    size_t p_len = 0;
    ssize_t p_read;
    while ((p_read = getline(&p_line, &p_len, pf)) != -1 && !is_match) {
      if (p_read > 0 && p_line[p_read - 1] == '\n') p_line[p_read - 1] = '\0';
      regex_t regex;
      int cflags = REG_EXTENDED | (flags.i == 1 ? REG_ICASE : 0);
      if (strlen(p_line) == 0) {
        is_match = 0;
      } else if (regcomp(&regex, p_line, cflags) == 0) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) is_match = 1;
        regfree(&regex);
      }
    }
    free(p_line);
    fclose(pf);
  }
  return is_match;
}

void check_and_print_line(const char* filename, struct GrepFlags flags,
                          int line_cnt, int is_several, regex_t* regex,
                          char* line, ssize_t read_status) {
  if (flags.c == 0 && flags.l == 0) {
    if (flags.o == 1 && flags.v == 0)
      print_only_matching(filename, flags, line_cnt, is_several, regex, line);
    else {
      if (is_several == 1 && flags.h == 0) printf("%s:", filename);
      if (flags.n == 1) printf("%d:", line_cnt);
      printf("%s", line);
      if (line[read_status - 1] != '\n') putchar('\n');
    }
  }
}

void print_summary(const char* filename, struct GrepFlags flags, int is_several,
                   int matches) {
  if (flags.c == 1) {
    if (is_several == 1 && flags.h == 0) printf("%s:", filename);
    if (flags.l == 1 && matches > 0)
      printf("1\n");
    else
      printf("%d\n", matches);
  }
  if (flags.l == 1 && matches > 0) printf("%s\n", filename);
}

void read(const char* filename, struct GrepFlags flags, const char* pattern,
          int is_several_files) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    if (flags.s == 0) s21_print_error("s21_grep", filename);
  } else {
    int exit_code = 1;
    regex_t regex;
    if (flags.f == 0) {
      int cflags = REG_EXTENDED;
      if (flags.i == 1) cflags |= REG_ICASE;
      if (regcomp(&regex, pattern, cflags) != 0) {
        if (flags.s == 0) fprintf(stderr, "No coincidence");
        exit_code = 0;
      }
    }
    if (exit_code == 1) {
      char* line = NULL;
      size_t len = 0;
      ssize_t read_status;
      int line_cnt = 0;
      int matches = 0;
      while ((read_status = getline(&line, &len, file)) != -1) {
        line_cnt++;
        int is_match = (flags.f == 1)
                           ? match_file_patterns(line, pattern, flags)
                           : (regexec(&regex, line, 0, NULL, 0) == 0);
        if (flags.v == 1) is_match = !is_match;
        if (is_match) {
          matches++;
          check_and_print_line(filename, flags, line_cnt, is_several_files,
                               &regex, line, read_status);
        }
      }
      print_summary(filename, flags, is_several_files, matches);
      free(line);
      if (flags.f == 0) regfree(&regex);
    }
    fclose(file);
  }
}

int main(int argc, char* argv[]) {
  int exit_code = 0;
  struct GrepFlags flags = {0};
  if (argc < 3) {
    fprintf(stderr, "Error");
    exit_code = 1;
  }
  int opt;
  const char* pattern = NULL;
  int is_several_files = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    if (opt == 'e') {
      flags.e = 1;
      pattern = optarg;
    } else if (opt == 'f') {
      flags.f = 1;
      pattern = optarg;
    } else if (opt == 'i') {
      flags.i = 1;
    } else if (opt == 'v') {
      flags.v = 1;
    } else if (opt == 'c') {
      flags.c = 1;
    } else if (opt == 'l') {
      flags.l = 1;
    } else if (opt == 'n') {
      flags.n = 1;
    } else if (opt == 'h') {
      flags.h = 1;
    } else if (opt == 's') {
      flags.s = 1;
    } else if (opt == 'o') {
      flags.o = 1;
    }
  }
  if (flags.e == 0 && flags.f == 0 && optind < argc) {
    pattern = argv[optind];
    optind++;
  }
  if (pattern == NULL) {
    if (flags.s == 0) fprintf(stderr, "Error");
    exit_code = 1;
  }
  if (argc - optind > 1) is_several_files = 1;
  for (int i = optind; i < argc; i++)
    read(argv[i], flags, pattern, is_several_files);
  return exit_code;
}