#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <assert.h>

#define MAX_LEN 100

int count = 0;

int isProblemType (char o) {
    return !(o != '?' && o != '#');
}

int isDigitOnly (char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}



long long getSectionValue(const char *str, int start, int end) {
    char buffer[32]; // Sufficient for large numbers
    strncpy(buffer, str + start, end - start);
    buffer[end - start] = '\0';
    return atoll(buffer);
}

void printSplit(const char *str, int *splitPositions, int splitCount) {
    printf("* ");
    int start = 0;
    for (int i = 0; i <= splitCount; i++) {
        int end = (i < splitCount) ? splitPositions[i] : strlen(str);
        for (int j = start; j < end; j++) {
            putchar(str[j]);
        }
        if (i < splitCount) putchar(',');
        start = end;
    }
    putchar('\n');
}

// Recursive function to generate valid splits
void generateSplits(const char *str, int *splitPositions, int splitCount, int index, int isVerbose) {
    int n = strlen(str);

    if (index >= n) { 
        count++;
        if (isVerbose) printSplit(str, splitPositions, splitCount);
        return;
    }

    int lastStart = (splitCount == 0) ? 0 : splitPositions[splitCount - 1];
    long long lastValue = getSectionValue(str, lastStart, index);

    // Option 1: Add the current index as a split position
    splitPositions[splitCount] = index;

    int nextStart = index;
    long long nextValue = getSectionValue(str, nextStart, n);

    if (lastValue % 2 == 1 || lastValue <= nextValue) {
        generateSplits(str, splitPositions, splitCount + 1, index + 1, isVerbose);
    }

    // Option 2: Do not split at this position
    generateSplits(str, splitPositions, splitCount, index + 1, isVerbose);
}

void solve_problem(char* code, int isVerbose) {
    

    int len = strlen(code);

    int *splitPositions = (int *)malloc(len * sizeof(int));

    count = 0;
    generateSplits(code, splitPositions, 0, 1, isVerbose);

    printf("Celkem: %d", count);

    return;
}

int readInput() {

    char code[MAX_LEN];
    char op;

    printf("Posloupnost:\n");

    // Read the input line formatted as {?+#}.{0-9}.{0-9}*
    // ? and # decide the operation, the numbers are the code
    while (1) {

        int conversions = scanf(" %c %s", &op, code);

        if (conversions == EOF) {
            break;
        }

        //printf("[DEBUG]\n%c %s\nproblemType = %c\ncode = %s\n", problemType, code, problemType, code);

        if (conversions != 2 || !isProblemType(op) || !isDigitOnly(code)) {
            //printf("[DEBUG]\n(conversions != 2) = %d\nisValidProblem = %d\nisDigitOnly = %d\n\n", (conversions != 2), isProblemType(problemType), isDigitOnly(code));
            return 0; // error
        }

        if (op == '?') {
            solve_problem(code, 1); // verbose solution
        } else {
            solve_problem(code, 0); // quiet solution
        }
    }

    return 1;
}

void tests() {

    return;
}

int main() {

    //tests();
    if (readInput() == 0) {
        printf("Nespravny vstup.\n");
    }

    

    return 0;

}