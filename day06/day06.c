#include <stdio.h>

#define BUFSZ 128

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

int main() {
    char linebuf[BUFSZ], codes[26]; 
    int count = 0, count2 = 0, groupsz = 0, i;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) ERROR("Unable to load input.txt\n");

    memset(codes, 0, 26);

    while (fgets(linebuf, BUFSZ-1, fp)) {
        char *p = linebuf;
        i = strspn(linebuf, "abcdefghijklmnopqrstuvwxyz");

        if (i > 0) {
            linebuf[i] = '\0';
            ++groupsz;
            for ( ; *p; ++p )
                if (*p >= 'a' && *p <= 'z') {
                    if (codes[*p -'a'] == 0) ++count;
                    codes[*p - 'a']++;
                }
        }
        else {
            for (i=0; i<26; ++i)
                if (codes[i] == groupsz)
                    ++count2;

            memset(codes, 0, 26);
            groupsz = 0;
        }
    }

    for (i=0; i<26; ++i)
        if (codes[i] == groupsz)
            ++count2;


    printf("Found %d answers (part 1)\n", count);
    printf("Found %d answers (part 2)\n", count2);
}
