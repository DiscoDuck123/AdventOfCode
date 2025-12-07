#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct sums {
    unsigned long sums1;
    unsigned long sums2;
} sums;


int getFileLen(FILE *in) {
    fseek(in, 0, SEEK_END);
    int len = ftell(in);
    fseek(in, 0, SEEK_SET);

    return len;
}

char *getCharsAfter(char *list, char symbol) {
    char *point = strchr(list, symbol); 
    if (!point || point == list) return NULL; 
    return point + 1; 
}

char *getCharsBefore(char *list, char symbol) {
    char *point = strchr(list, symbol); 
    if (!point) return NULL; 
    
    size_t stringLen = point - list; 
    char *range = malloc(stringLen + 1); 
    memcpy(range, list, stringLen); 
    range[stringLen] = '\0'; 
    return range;
}

int getNumDigits(long num) {
    int digits = 0;
    while(num != 0) {
        num /= 10;
        digits += 1;
    }
    if (digits % 2 != 0) digits += 1;

    return digits;
}

bool isRepeatedNum(char *s) {
    int len = strlen(s);

    for (int i = 1; i <= len / 2; i++) {
        if (len % i != 0) continue;

        int repeats = len / i;
        bool isRepeated = true;
        for (int r = 1; r < repeats; r++) {
            if (strncmp(s, s + r * i, i) != 0) {
                isRepeated = false;
                break;
            }
        }

        if (isRepeated) return isRepeated;
    }

    return false;
}

sums sumInvalidIDs(char *range) {
    char *lb = getCharsBefore(range, '-');
    char *ub = getCharsAfter(range, '-');

    unsigned long low  = strtoul(lb, NULL, 10);
    unsigned long high = strtoul(ub, NULL, 10);
    free(lb);

    sums s = {0, 0};
    for (unsigned long i = low; i <= high; i++) {
        int digits = getNumDigits(i);

        char buf[32];
        snprintf(buf, sizeof(buf), "%lu", i);

        // Part 1
        if (digits % 2 == 0) {
            if (strncmp(buf, buf + digits/2, digits/2) == 0) s.sums1 += i;
        }

        // Part 2
        if (isRepeatedNum(buf)) s.sums2 += i;
    }

    return s;
}


int main(void) {
    FILE *input = fopen("input.txt", "r");
    int len = getFileLen(input);
    char *rangeList = malloc(len + 1);

    fgets(rangeList, len + 1, input);
    char *tok = strtok(rangeList, ",");
    
    sums p = {0, 0};
    sums n = {0, 0};
    while (tok != NULL) {
        n = sumInvalidIDs(tok);
        p.sums1 += n.sums1;
        p.sums2 += n.sums2;
        tok = strtok(NULL, ",");
    }

    printf("Part 1 Password: %lu\nPart 2 Password: %lu\n", p.sums1, p.sums2);
    free(rangeList);
    return 0;
}
