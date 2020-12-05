#include <stdio.h>

#define BUFSZ 64

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

int line(buffer) 
    char *buffer;
{
    int a, b, n = 0;
    char c, pass[BUFSZ], *p = pass;

    if ( sscanf(buffer, "%d-%d %c: %s", &a, &b, &c, pass) != 4 )
        ERROR("Unable to parse password line\n");

    while (*p) if (*p++ == c) ++n;
    return n >= a && n <= b;
}

int main() {
    char linebuf[BUFSZ];
    int valid = 0;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    while (fgets(linebuf, BUFSZ-1, fp))
        valid += line(linebuf);
    fclose(fp);

    printf("Found %d valid passwords\n", valid);
}
