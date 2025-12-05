#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 4107
#define MAX_LEN 6

typedef struct pass {
    int pass1;
    int result1;

    int pass2;
    int result2;
} pass;


void getRotations(FILE *list, char rotations[][MAX_LEN]) {
    for (int i = 0; i < FILE_LEN; i++) {
        fgets(rotations[i], MAX_LEN, list);
        rotations[i][strcspn(rotations[i], "\n")] = '\0';
    }
}

pass countRotations(char rotations[][MAX_LEN]) {
    pass p = {0, 50, 
              0, 50};

    for (int i = 0; i < FILE_LEN; i++) {
        int sign = (rotations[i][0] == 'L') ? -1 : 1;
        int num = strtol(rotations[i] + 1, NULL, 10);
        
        p.result1 += sign * num;
        if (p.result1 % 100 == 0) p.pass1++;

        for (int steps = 0; steps < num; steps++) {
            p.result2 = (p.result2 + sign + 100) % 100;
            if (p.result2 == 0) p.pass2++;
        }
    }

    return p;
}

int main(void) {
    FILE *in = fopen("input.txt", "r");
    char rotations[FILE_LEN][MAX_LEN];

    getRotations(in, rotations);
    fclose(in);

    pass password = countRotations(rotations);
    printf("Part 1 Password: %d\n", password.pass1);
    printf("Part 2 Password: %d\n", password.pass2);
    return 0;
}
