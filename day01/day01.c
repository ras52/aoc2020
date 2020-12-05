#include <stdio.h>

#define N_VALS 256
#define BUFSZ 16

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

#define TOTAL 2020

int main() {
    char linebuf[BUFSZ];
    int vals[N_VALS], n = 0, i, j, k, rest;
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

    for (i=0; i<n; ++i) {
        if (vals[i] > TOTAL/3) continue;
        rest = TOTAL - vals[i];
        for (j=0; j<n; ++j) {
            if (i == j || vals[j] > rest/2 || vals[j] < vals[i]) continue;
            for (k=0; k<n; ++k)
                if (k != i && k != j && vals[j] + vals[k] == rest)
                    printf("%d * %d * %d = %d\n", vals[i], vals[j], vals[k],
                           vals[i] * vals[j] * vals[k]);
        }
    }

    return 0;
}
