#include <stdio.h>

int main () {
    int hourA, minuteA, hourB, minuteB;

    scanf("%d:%d", &hourA, &minuteA);
    if (hourA < 0 || hourA > 24 || minuteA < 0 || minuteA > 60) {
        printf("Incorrect input!\n");
        return 1;
    }
    scanf("%d:%d", &hourB, &minuteB);
    if (hourB < 0 || hourB > 24 || minuteB < 0 || minuteB > 60) {
        printf("Incorrect input!\n");
        return 1;
    }
    
    int timeA = hourA * 60 + minuteA;
    int timeB = hourB * 60 + minuteB;
    int timeResult = 0;

    if (timeB > timeA) {
        timeResult = timeB - timeA;
    } else {
        timeResult = (timeB + 24*60) - timeA;
    }
    printf("%d:%02d\n", (timeResult / 60), (timeResult % 60));

    return 0;
}