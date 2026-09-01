#include <stdio.h>
#include <getopt.h>

struct CatFlags {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
};

void read(const char *filename, struct CatFlags flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "No");
        return;
    }
    int current_char;
    int cnt = 1;
    int is_new_line = 1;
    while ((current_char = fgetc(file)) != EOF) {
        if (is_new_line == 1) {
            if (flags.b == 1 && current_char != '\n') {
                printf("%6d\t", cnt);
                cnt++;
            }
            if (flags.n == 1) {
                printf("%6d\t", cnt);
                cnt++;
            }
            is_new_line = 0;
        }
        if ((flags.e == 1 || flags.E == 1) && current_char == '\n') {
            putchar('$');
        }
        if (flags.v == 1 && current_char != '\n' && current_char != '\t') {
            if (current_char < 32) {
                putchar('^');
                putchar(current_char + 64);
            } else if (current_char == 128);
        }
        putchar(current_char);
        if (current_char == '\n') {
            is_new_line = 1;
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    struct CatFlags flags = {0};
    int opt;
    while ((opt = getopt(argc, argv, "benstTvE")) != -1) {
        switch (opt)
        {
        case 'b':
            flags.b = 1;
            break;
        case 'e':
            flags.e = 1;
            flags.v = 1;
            break;
        case 'n':
            flags.n = 1;
            break;
        case 's':
            flags.s = 1;
            break;
        case 't':
            flags.t = 1;
            break;
        case 'E':
            flags.E = 1;
            break;
        default:
            break;
        }
    }
    for (int i = optind; i < argc; i++) {
        read(argv[i], flags);
    }
    return 0;
}