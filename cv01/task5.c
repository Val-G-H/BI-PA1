#include <stdio.h>

int main () {
    int a, b, c;
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("c = ");
    scanf("%d", &c);
    int porvch = 2 * (a*b + a*c + b*c);
    int objem = a * b * c;
    printf("Porvch: %d\n", porvch);
    printf("Objem: %d\n", objem);
    return 0;
}touch