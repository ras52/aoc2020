#include <stdio.h>

#define BUFSZ 64
#define MAX_LINES 512

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

int main() {
    int n = 0, x = 0, y = 0, len, trees = 0;
    char *lines[MAX_LINES], *line;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    while (1) {
        line = (char*)malloc(BUFSZ);
        if (!fgets(line, BUFSZ-1, fp)) 
            break;
        lines[n++] = line;
        if (n == MAX_LINES) ERROR("Too many lines\n");
    }

    while ( y < n ) {
       line = lines[y];
       len = strlen(line) - 1;
       trees += line[x % len] == '#';
       x += 3;
       y++;
    }

    printf("Read %d lines and %d trees\n", n, trees);
    return 0;
}
