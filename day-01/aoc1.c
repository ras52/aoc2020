#include <stdio.h>

#define N_VALS 256
#define BUFSZ 16

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

#define TOTAL 2020

int main() {
    char linebuf[BUFSZ];
    int vals[N_VALS], n = 0, i, j;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    while (fgets(linebuf, BUFSZ-1, fp)) {
        vals[n++] = atoi(linebuf);
        if (n == N_VALS) ERROR("Too many values\n");
    }
    fclose(fp);

    for (i=0; i<n; ++i) { 
        if (vals[i] > TOTAL/2) continue;
        for (j=0; j<n; ++j)
            if (i != j && vals[i] + vals[j] == TOTAL)
                printf("%d * %d = %d\n", vals[i], vals[j], vals[i]*vals[j]);
    }
    return 0;
}
