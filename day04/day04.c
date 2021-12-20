#include <stdio.h>
#include <string.h>

#define BUFSZ 128

#define ERROR(MSG) (fputs(MSG, stderr), exit(1))

struct passport {
  char *byr, *iyr, *eyr, *hgt, *hcl, *ecl, *pid, *cid;
};

void destpass(passport)
    struct passport *passport;
{
    if (passport->byr) free(passport->byr);
    if (passport->iyr) free(passport->iyr);
    if (passport->eyr) free(passport->eyr);
    if (passport->hgt) free(passport->hgt);
    if (passport->hcl) free(passport->hcl);
    if (passport->ecl) free(passport->ecl);
    if (passport->pid) free(passport->pid);
    if (passport->cid) free(passport->cid);
}

/* Is valid per part one of challenge? */
int is_valid(passport)
    struct passport* passport;
{
    return passport->byr && passport->iyr && passport->eyr && passport->hgt
        && passport->hcl && passport->ecl && passport->pid;
}

int is_valid2(passport)
    struct passport* passport;
{
    int i;
    char *nptr;

    if (!is_valid(passport)) return 0;

    i = strtoul(passport->byr, &nptr, 10);
    if (*nptr || i < 1920 || i > 2002) return 0;

    i = strtoul(passport->iyr, &nptr, 10);
    if (*nptr || i < 2010 || i > 2020) return 0;

    i = strtoul(passport->eyr, &nptr, 10);
    if (*nptr || i < 2020 || i > 2030) return 0;

    i = strtoul(passport->hgt, &nptr, 10);
    if (strcmp(nptr, "cm") == 0) { 
      if (i < 150 || i > 193) return 0;
    }
    else if (strcmp(nptr, "in") == 0) {
      if (i < 59  || i > 76) return 0;
    }
    else return 0;

    if (strlen(passport->hcl) != 7 || passport->hcl[0] != '#' ||
        strspn(passport->hcl + 1, "0123456789abcdef") != 6) return 0;

    if (strcmp(passport->ecl, "amb") && strcmp(passport->ecl, "blu") &&
        strcmp(passport->ecl, "brn") && strcmp(passport->ecl, "gry") &&
        strcmp(passport->ecl, "grn") && strcmp(passport->ecl, "hzl") &&
        strcmp(passport->ecl, "oth")) return 0;

    if (strlen(passport->pid) != 9 || strspn(passport->pid, "0123456789") != 9)
      return 0;

    return 1;
}

int main() {
    char linebuf[BUFSZ], sym[4], val[BUFSZ]; 
    int valid = 0, valid2 = 0;
    FILE *fp = fopen("input.txt", "r");
    struct passport passport;
    memset(&passport, 0, sizeof(struct passport));

    if (!fp) ERROR("Unable to load input.txt\n");
    
    sym[3] = 0; 
    while (fgets(linebuf, BUFSZ-1, fp)) {
        char *p = linebuf; int off, n = 0;
        while (sscanf(p, "%c%c%c:%s %n", &sym[0], &sym[1], &sym[2], 
                      val, &off) == 4) {
            if      (strcmp(sym, "byr") == 0) passport.byr = strdup(val);
            else if (strcmp(sym, "iyr") == 0) passport.iyr = strdup(val);
            else if (strcmp(sym, "eyr") == 0) passport.eyr = strdup(val);
            else if (strcmp(sym, "hgt") == 0) passport.hgt = strdup(val);
            else if (strcmp(sym, "hcl") == 0) passport.hcl = strdup(val);
            else if (strcmp(sym, "ecl") == 0) passport.ecl = strdup(val);
            else if (strcmp(sym, "pid") == 0) passport.pid = strdup(val);
            else if (strcmp(sym, "cid") == 0) passport.cid = strdup(val);
            n++; p += off;
        }
        if ( n == 0 ) {
            valid += is_valid(&passport);
            valid2 += is_valid2(&passport);
            destpass(&passport);
            memset(&passport, 0, sizeof(struct passport));
        }
    }
    valid += is_valid(&passport);
    valid2 += is_valid2(&passport);
    fclose(fp);

    printf("Found %d valid entries per part 1\n", valid);
    printf("Found %d valid entries per part 2\n", valid2);
}
