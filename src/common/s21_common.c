#include "s21_common.h"

void s21_print_error(const char* utility_name, const char* filename) {
  fprintf(stderr, "%s: %s: No such file or directory\n", utility_name,
          filename);
}
