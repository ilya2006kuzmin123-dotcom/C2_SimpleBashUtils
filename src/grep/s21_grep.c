#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct GrepFlags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
};

void read(const char* filename, struct GrepFlags flags, const char* pattern) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "No");
    return;
  }
  regex_t regex;
  int cflags = REG_EXTENDED;
  if (flags.i == 1) {
    cflags |= REG_ICASE;
  }
  if (regcomp(&regex, pattern, cflags) != 0) {
    fprintf(stderr, "No coincidence");
    fclose(file);
    return;
  }
  char* line = NULL;
  size_t len = 0;
  ssize_t read_status;
  while ((read_status = getline(&line, &len, file)) != -1) {
    int status = regexec(&regex, line, 0, NULL, 0);
    if (status == 0) {
        printf("%s", line);
        if (line[read_status - 1] != '\n') {
            putchar('\n');
        }
    }
  }
  free(line);
  regfree(&regex);
  fclose(file);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Error");
    return 1;
  }
  struct GrepFlags flags = {0};
  int opt;
  char* pattern = NULL;
  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
    //Все флаги тестить, -e -i на коленке сделаны, мб не работают, остальные не сделаны
      case 'e':
        flags.e = 1;
        pattern = optarg;
        break;
      case 'i':
        flags.i = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
      case 'c':
        flags.c = 1;
        break;
      case 'l':
        flags.l = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      default:
        break;
    }
  }
  if (flags.e == 0 && optind < argc) {
    pattern = argv[optind];
    optind++;
  }
  if (pattern == NULL) {
    fprintf(stderr, "Error");
    return 1;
  }
  for (int i = optind; i < argc; i++) {
    read(argv[i], flags, pattern);
  }
  return 0;
}