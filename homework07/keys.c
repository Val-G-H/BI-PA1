#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <assert.h>

#define MAX_LEN 100

int count = 0;
int call_count = 0;

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

int isValid(long long lastValue, long long nextValue) {
    //return (lastValue % 2 == 0 && lastValue <= nextValue);
    //printf("%lld <= %lld\n", lastValue, nextValue);
    return (lastValue % 2 == 1 || lastValue <= nextValue);
}

int isValidTwo(const char *str, int *splitPositions, int splitCount, int index) {
    
    printf("splitCount = %d\n", splitCount);
    
    for (int i = 0; i < 4; i++) {
        printf("splitPositions[%d] = %d\n", i, splitPositions[i]);
    }
    
    printf("\n\n");
    
    //int start = splitPositions[0]+1;
    int lastValue, nextValue;
    
    lastValue = getSectionValue(str, 0, splitPositions[0]);
    
    for (int i = 1; i < 3; i++) {
        
        if (splitPositions[i] == splitPositions[i+1]) break;
        
        //printf("start = %d\t", start);
        //printf("splitPositions[%d] = %d\n", i, splitPositions[i]);
        
        //printf("splitPositions[%d] = %d (%d)\n", i, splitPositions[i], splitPositions[i]-2);
        //printf("splitPositions[%d] = %d (%d)\n", i+1, splitPositions[i+1], splitPositions[i+1]-1);
        
        printf("splitPositions[%d] = %d (%d)\n", i, splitPositions[i], splitPositions[i]);
        printf("splitPositions[%d] = %d (%d)\n", i+1, splitPositions[i+1], splitPositions[i+1]);
        
        
        //nextValue = getSectionValue(str, start - 1, splitPositions[i]);
        nextValue = getSectionValue(str, splitPositions[i], splitPositions[i+1]);
        
        printf("%lld <= %lld\n", lastValue, nextValue);
        if (lastValue % 2 == 0 && lastValue > nextValue) {
            printf("OOGA BOOGA!\n");
        }
        
        
        
        lastValue = nextValue;
        
        
        
        //start = splitPositions[i] + 1;
    }
}

// Recursive function to generate valid splits
void generateSplits(const char *str, int *splitPositions, int splitCount, int index, int isVerbose) {
    call_count++;
    printf("#%d^\n", call_count);
    int n = strlen(str);

    if (index >= n) { 
        printf("BOING\tsplitCount = %d\n", splitCount);
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

    printf("\t%lld->%lld\n", lastValue, nextValue);
    /*
    if (lastValue % 2 == 1 || lastValue <= nextValue) {
        printf("\tPassed. generateSplits splitCount %d, index %d\n", splitCount + 1, index + 1);
        generateSplits(str, splitPositions, splitCount + 1, index + 1, isVerbose);
    } else {
        printf("\tNOT passed\n");
    }
    */
    
    //printf("\tisValid = %d\n", isValid(lastValue, nextValue));
    if (index > 1) {
    long long temp1 = getSectionValue(str, splitPositions[index-2], splitPositions[index-1]);
    long long temp2 = getSectionValue(str, splitPositions[index-3], splitPositions[index-2]);
    
    //printf("\tindex = %d, splitPositions[index-2] = %d, splitPositions[index-1] = %d, temp1 = %lld\n", index, splitPositions[index-2], splitPositions[index-1], temp1);
    //printf("\tindex = %d, splitPositions[index-3] = %d, splitPositions[index-2] = %d, temp2 = %lld\n", index, splitPositions[index-3], splitPositions[index-2], temp2);
    }
    
    if (isValid(lastValue, nextValue)) {
        printf("\tPassed. generateSplits splitCount %d, index %d\n", splitCount + 1, index + 1);
        generateSplits(str, splitPositions, splitCount + 1, index + 1, isVerbose);
    } else {
        printf("\tNOT passed\n");
    }
    
    //generateSplits(str, splitPositions, splitCount, index + 1, isVerbose);

    // Option 2: Do not split at this position
    
    if (isValid(lastValue, nextValue)) {
        isValidTwo(str, splitPositions, splitCount, index);
        printf("\tUnconditional. generateSplits splitCount %d, index %d\n", splitCount, index + 1);
        generateSplits(str, splitPositions, splitCount, index + 1, isVerbose);
    }
    
    return;
}

void solve_problem(char* code, int isVerbose) {
    

    int len = strlen(code);

    int *splitPositions = (int *)malloc((len-1) * sizeof(int));

    count = 0;
    generateSplits(code, splitPositions, 0, 1, isVerbose);

    printf("Celkem: %d", count);
    free(splitPositions);

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