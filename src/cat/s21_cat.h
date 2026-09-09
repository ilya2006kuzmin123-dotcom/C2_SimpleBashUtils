#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>

struct CatFlags {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
    int T;
};

void print_formatted_char(int current_char, struct CatFlags flags);
void read(const char* filename, struct CatFlags flags, int* cnt);

#endif