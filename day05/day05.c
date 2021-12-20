#include <stdio.h>

#define BUFSZ 128

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

int main() {
    char linebuf[BUFSZ]; char seats[1024]; 
    int highest = 0, i;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    memset(seats, 0, 1024);

    while (fgets(linebuf, BUFSZ-1, fp)) {
        int n = 0;
        for (i=0; i<7; ++i)
            n = n << 1 | linebuf[i] == 'B';
        for (i=7; i<10; ++i)
            n = n << 1 | linebuf[i] == 'R';
        seats[n] = 1;
        if (n > highest) highest = n;
    }

    printf("Highest seat number is %d\n", highest);

    for (i=0; i<1024; ++i)
        if (seats[i]) break;
    printf("First seat is %d\n", i);

    for (; i<1024; ++i)
        if (!seats[i]) {
            printf("Seat %d is free\n", i);
            break;
        }
}
