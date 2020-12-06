#include <stdio.h>

#define BUFSZ 64
#define MAX_LINES 512

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

unsigned slope(lines, n, dx, dy) 
    char **lines;
{
    unsigned x = 0, y = 0, len, trees = 0;
    char *line;
    while ( y < n ) {
       line = lines[y];
       len = strlen(line) - 1;
       trees += line[x % len] == '#';
       x += dx;
       y += dy;
    }

    printf("Slope %d,%d hits %d trees\n", dx, dy, trees);
    return trees;
}

int main() {
    unsigned n = 0, prod = 1;
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
    fclose(fp);

    prod *= slope(lines, n, 1, 1);
    prod *= slope(lines, n, 3, 1);
    prod *= slope(lines, n, 5, 1);
    prod *= slope(lines, n, 7, 1);
    prod *= slope(lines, n, 1, 2);
    printf("Multiplied gives %u\n", prod);
    return 0;
}
