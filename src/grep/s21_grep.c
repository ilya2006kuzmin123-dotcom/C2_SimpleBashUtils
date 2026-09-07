#include <stdio.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>

struct GrepFlags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
};

void read(const char* filename, struct GrepFlags flags) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "No");
        return;
    }
}

int main(int argc, char* argv[]) {
    int ans = 1;
    if (argc < 3) {
        fprintf(stderr, "Error");
    } else {
        regex_t regex;
        struct GrepFlags flags = {0};
        int status;
        int opt;
        while(opt == getopt(argc, argv, "benstTvE") != -1) {
            switch (opt)
            {
            case 'e':
                flags.e = 1;
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
        char* pattern = argv[1];
        if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
            fprintf(stderr, "Error");
            return 1;
        }
        for(int i = optind; i < argc; i++) {
                read(argv[i], flags);
        }
        regfree(&regex);
    }
    return 0;
}