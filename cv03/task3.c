#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

int eq(double left, double right)
{
    return fabs(left - right) <= DBL_EPSILON * 500 * (fabs(left) + fabs(right));
}

int main () {
    
    double currentCalculation;
    double oldCalculation;
    int input;
    char operation;
    bool firstEquals = true;
    bool closeEquation = false;

    int ooga = scanf("%d", &input); 
    
    if (ooga != 1) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    //printf("%d; %d", ooga, currentCalculation);

    currentCalculation = input;

    while (1) {

        int conversions = scanf(" %c %d", &operation, &input);

        //printf("\n\ncurrentCalculation = %g\n operation = %c\ninput = %d\n\n", currentCalculation, operation, input);

        if (conversions == EOF) {
            break;
        }
        
        if (conversions != 2) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (operation == '*') {
            currentCalculation *= input;
        } else if (operation == '/') {
            currentCalculation /= input;
        } else if (operation == '=') {
                closeEquation = true;
                if (firstEquals) {
                    printf("%g", currentCalculation);
                    firstEquals = false;
                    oldCalculation = currentCalculation;
                    currentCalculation = input;
                }

                if(eq(oldCalculation, currentCalculation)) {
                    printf(" = %g", currentCalculation);
                } else {
                    printf(" != %g", currentCalculation);
                }

                oldCalculation = currentCalculation;
                currentCalculation = input;
        }

        //printf("\n\ncurrentCalculation = %g\n operation = %c\ninput = %d\n\n", currentCalculation, operation, input);
    }
    if (firstEquals) {
        printf("%g", currentCalculation);
    }
    printf("\n");
    //printf("%g\n", currentCalculation);

    return 0;
}