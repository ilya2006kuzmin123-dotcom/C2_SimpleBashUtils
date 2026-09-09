#ifndef S21_GREP_H_
#define S21_GREP_H_

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GrepFlags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

void print_only_matching(const char* filename, struct GrepFlags flags,
                         int line_cnt, int is_several, regex_t* regex,
                         char* line);
int match_file_patterns(const char* line, const char* patterns_file,
                        struct GrepFlags flags);
void check_and_print_line(const char* filename, struct GrepFlags flags,
                          int line_cnt, int is_several, regex_t* regex,
                          char* line, ssize_t read_status);
void print_summary(const char* filename, struct GrepFlags flags, int is_several,
                   int matches);
void read(const char* filename, struct GrepFlags flags, const char* pattern,
          int is_several_files);

#endif