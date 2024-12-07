#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <assert.h>

#define MAX_LEN 100

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

void solve_problem(char* code, int isVerbose) {
    int count = 0;

    // ooga

    return count;
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