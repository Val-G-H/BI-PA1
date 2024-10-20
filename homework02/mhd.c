#include <stdio.h>
#include <stdint.h>

int isEven(int a) {
    return (a % 2 == 1) ? 0 : 1;
}

int findLCM(int a, int b) {
    int max = (a > b) ? a : b;

    int lcm = max;

    while ((lcm % a != 0) || (lcm % b != 0)) {
        lcm += max;
    }
    return lcm;
}

int main() {
    // input for A
    int int1_h, int2_h, dep2_h;
    short int1_m, int2_m, dep2_m;

    printf("Interval spoje #1:\n");
    int conversions = scanf("%d:%hd", &int1_h, &int1_m);
    if (conversions != 2 || int1_h < 0 || int1_m < 0 || int1_m >= 60) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int int1 = int1_h * 60 + int1_m;

    printf("Interval spoje #2:\n");
    conversions = scanf("%d:%hd", &int2_h, &int2_m);
    if (conversions != 2 || int2_h < 0 || int2_m < 0 || int2_m >= 60) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int int2 = int2_h * 60 + int2_m;

    printf("Cas od odjezdu spoje #2:\n");
    conversions = scanf("%d:%hd", &dep2_h, &dep2_m);
    if (conversions != 2 || dep2_h < 0 || dep2_m < 0 || dep2_m >= 60) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int dep2 = dep2_h * 60 + dep2_m;

    if (dep2 > int2 || dep2 == 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int counting1 = int1;
    int counting2 = int2 - dep2;

    //printf("counting1 = %lld\ncounting2 = %lld\n", counting1, counting2);

    if (isEven(int1_m) && isEven(int2_m) && isEven(dep2_m)) { 
        printf("Spoj #2 nikdy nebude odjizdet 1 minutu po prijezdu spoje #1.\n");
        return 0;
    }

    if (0 == (counting2 - 1)) {
        printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 prave nyni.\n");
        return 0;
    }

    //int result = findLCM(counting1, counting2);

    //printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 za %d:%02d.\n", (result / 60), (result % 60));


    
    while (1) {

        
        if (counting1 >= counting2) {
            counting2 += int2;
        } else {
            counting1 += int1;
        }
        

       
        
        if (counting1 == (counting2 - 1)) {
            printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 za %d:%02d.\n", (counting1 / 60), (counting1 % 60));
            break;
        }
        

    }
    

    return 0;
}
