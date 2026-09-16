#include "s21_cat.h"

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