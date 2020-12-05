#include <stdio.h>

#define BUFSZ 64

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

void line(buffer, valid1, valid2) 
    char *buffer;
    int *valid1, *valid2;
{
    int a, b, n = 0;
    char c, pass[BUFSZ], *p = pass;

    if ( sscanf(buffer, "%d-%d %c: %s", &a, &b, &c, pass) != 4 )
        ERROR("Unable to parse password line\n");

    while (*p) if (*p++ == c) ++n;
    *valid1 += n >= a && n <= b;
    *valid2 += pass[a-1] == c ^ pass[b-1] == c;
}

int main() {
    char linebuf[BUFSZ];
    int valid1 = 0, valid2 = 0;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    while (fgets(linebuf, BUFSZ-1, fp))
        line(linebuf, &valid1, &valid2);
    fclose(fp);

    printf("Found %d valid passwords per policy 1\n", valid1);
    printf("Found %d valid passwords per policy 2\n", valid2);
}
