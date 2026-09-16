#include "s21_grep.h"

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