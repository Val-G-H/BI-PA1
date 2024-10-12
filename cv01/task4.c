#include <stdio.h>

int main () {
    int a, b;
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    int obvod = 2 * (a + b);
    int obsah = a * b;
    printf("Obvod: %d\n", obvod);
    printf("Obsah: %d\n", obsah);
    return 0;
}