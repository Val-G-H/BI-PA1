#include <stdio.h>
#include <limits.h>

int test_run(char *test_case, char *int1_prompt, char *int2_prompt, char *dep2_prompt, char *dep2n) {
    int int1_h, int2_h, dep2_h;
    short int1_m, int2_m, dep2_m;

    printf("=== %s: 1) %s 2) %s 3) %s 4) %s ===\n", test_case, int1_prompt, int2_prompt, dep2_prompt, dep2n);

    // printf("Interval spoje #1:\n");
    int conversions = sscanf(int1_prompt, "%d:%hd", &int1_h, &int1_m);
    if (conversions != 2 || int1_h < 0 || int1_m < 0 || int1_m >= 60) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int int1 = int1_h * 60 + int1_m;

    // printf("Interval spoje #2:\n");
    conversions = sscanf(int2_prompt, "%d:%hd", &int2_h, &int2_m);
    if (conversions != 2 || int2_h < 0 || int2_m < 0 || int2_m >= 60) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int int2 = int2_h * 60 + int2_m;

    // printf("Cas od odjezdu spoje #2:\n");
    conversions = sscanf(dep2_prompt, "%d:%hd", &dep2_h, &dep2_m);
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

    if (0 == (counting2 - 1)) {
        printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 prave nyni.\n");
        return 0;
    }

    for (int i = 0; i < INT_MAX; i++) {
        if (counting1 >= counting2) {
            counting2 += int2;
        } else {
            counting1 += int1;
        }

        if (counting1 == (counting2 - 1)) {
            printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 za %d:%02d.\n", (counting1 / 60), (counting1 % 60));
            break;
        }

        if (i == INT_MAX - 1) {
            printf("Spoj #2 nikdy nebude odjizdet 1 minutu po prijezdu spoje #1.\n");
            return 1;            
        }
    }

    return 0;
}    

int main() {
    test_run("0000", "0:24", "0:44", "0:27", "3:12");
    test_run("0001", "0:17", "0:12", "0:4", "3:07");
    test_run("0002", "0:17", "0:12", "0:11", "just now");
    test_run("0003", "0:16", "0:12", "0:6", "never");
    test_run("0004", "0:16", "0:12", "0:15", "Invalid");

    test_run("0006", "0:0", "0:1", "0:1", "Invalid");

    return 0;
}