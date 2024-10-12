#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int eq(double left, double right) {
    return fabs(left-right) < 0.0000001 * (fabs(left) + fabs(right));
}

bool jePravouhly(double a, double b, double c) {
    double bigboy, smallboy;
    if (c > a && c > b) { bigboy = c*c; smallboy = a*a + b*b; }
    if (b > c && b > a) { bigboy = b*b; smallboy = a*a + c*c; }
    if (a > c && a > b) { bigboy = a*a; smallboy = c*c + b*b; }
    return eq(smallboy, bigboy); 
}

int main () {
    double a, b, c;
    char ooga;

    printf("Zadej delky stran:");
    if (scanf(" [ %lf ; %lf ; %lf %c", &a, &b, &c, &ooga) != 4 || ooga != ']') {
        printf("\nNespravny vstup.\n");
        return 1;
    }

    double obvod = a + b + c;
    printf("\nObvod = %g\n", obvod);

    if(jePravouhly(a, b, c)) printf("Trojuhelnik je pravouhly.\n");
    else printf("Trojuhelnik neni pravouhly.\n");  

    return 0;
}