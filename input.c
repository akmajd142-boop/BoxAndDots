#include <stdio.h>
#include "input.h"

int readMove(int *r1, int *c1, int *r2, int *c2) {
    char line[256];
    char extra;

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }

        // Discard remaining characters if input is too long.
        int hasNewline = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {
                hasNewline = 1;
                break;
            }
        }

        if (!hasNewline) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            printf("Input too long. Try again:\n");
            continue;
        }

        // Require exactly four integers.
        int count = sscanf(line, " %d %d %d %d %c",
                           r1, c1, r2, c2, &extra);

        if (count == 4) {
            return 1;
        }

        printf("Invalid input. Enter four integers "
               "(example: 0 0 0 1):\n");
    }
}

