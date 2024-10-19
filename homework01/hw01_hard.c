#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h> // For int64_t
#include <stdlib.h> // Include this header for llabs
#include <inttypes.h> // For PRId64

// Union for extracting integer representation of a double
union Double_t {
    double d;
    int64_t i;
};

int eq(double left, double right)
{
    //return fabs(left - right) <= DBL_EPSILON * 100 * (fabs(left) + fabs(right));
    return fabs(left - right) <= 1e-10;
}

struct Point {
    double x, y;
};

double vectorDotProduct(struct Point a, struct Point b, struct Point c, struct Point d) {
    return (b.x - a.x) * (b.y - a.y) + (d.x - c.x) * (d.y - c.y);
}

double vectorLength(struct Point a, struct Point b) {
    return sqrt( (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) );
}

int main() {

    struct Point a, b, c;
    char closingBracket = '\0';

    // input for A
    printf("Bod A:\n");
    int conversions = scanf(" [ %lf , %lf %c", &(a.x), &(a.y), &closingBracket);
    if (conversions != 3) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';

    // input for B
    printf("Bod B:\n");
    conversions = scanf(" [ %lf , %lf %c", &(b.x), &(b.y), &closingBracket);
    if (conversions != 3) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';
    
    // input for C
    printf("Bod C:\n");
    conversions = scanf(" [ %lf , %lf %c", &(c.x), &(c.y), &closingBracket);
    if (conversions != 3) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';

    // if three points are on the same line no parallelogram can be created
    // if three points are on the same line the area of the triangle they make up is 0
    double area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (eq(area, 0)) {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 1;
    }



    // calculate the points
    struct Point newA, newB, newC;

    // fourth point location
    newA.x = c.x + b.x - a.x;
    newA.y = c.y + b.y - a.y;
    newB.x = a.x + c.x - b.x;
    newB.y = a.y + c.y - b.y;
    newC.x = b.x + a.x - c.x;
    newC.y = b.y + a.y - c.y;

    // figure flags
    bool AisRight = false;
    bool BisRight = false;
    bool CisRight = false;
    bool AisEqual = false;
    bool BisEqual = false;
    bool CisEqual = false;

    // angles
    double angleA = vectorDotProduct(a, b, a, c);
    double angleB = vectorDotProduct(b, a, b, c);
    double angleC = vectorDotProduct(c, a, c, b);

    //printf("angleA = %.20lf\n", angleA);

    //printf("%.20lf < %.20lf, result is %d\n", angleA, 0.0000, (eq(angleA, 0.0)));
    
    /*
    if(eq(angleA, 0)) printf("figure from A' has a right angle\n");
    else printf("figure from A' doesn't have a right angle\n");
    if(eq(angleB, 0)) printf("figure from B' has a right angle\n");
    else printf("figure from B' doesn't have a right angle\n");
    if(eq(angleC, 0)) printf("figure from C' has a right angle\n");
    else printf("figure from C' doesn't have a right angle\n");
    */

    // an angle is right if the dot product of two vectors originating from this angle is 0
    if(eq(angleA, 0)) AisRight = true;
    if(eq(angleB, 0)) BisRight = true;
    if(eq(angleC, 0)) CisRight = true;

    // sides needed to find out if the figures have all sides equal
    double ab = vectorLength(a, b);
    double ac = vectorLength(a, c);
    double newAb = vectorLength(newA, b);
    double aNewB = vectorLength(a, newB);
    double aNewC = vectorLength(a, newC);

    /*
    if(eq(ab, newAb)) printf("figure from A' has all sides equal\n");
    else printf("figure from A' doesn't have all sides equal\n");
    if(eq(ab, aNewB)) printf("figure from B' has all sides equal\n");
    else printf("figure from B' doesn't have all sides equal\n");
    if(eq(ac, aNewC)) printf("figure from C' has all sides equal\n");
    else printf("figure from C' doesn't have all sides equal\n");
    */

    // all sides are equal if two touching sides are equal
    if(eq(ab, newAb)) AisEqual = true;
    if(eq(ab, aNewB)) BisEqual = true;
    if(eq(ac, aNewC)) CisEqual = true;

    printf("A': [%g,%g], ", newA.x, newA.y);
    if (AisEqual == true && AisRight) printf("ctverec\n");
    else if (AisEqual) printf("kosoctverec\n");
    else if (AisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    printf("B': [%g,%g], ", newB.x, newB.y);
    if (BisEqual == true && BisRight) printf("ctverec\n");
    else if (BisEqual) printf("kosoctverec\n");
    else if (BisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    printf("C': [%g,%g], ", newC.x, newC.y);
    if (CisEqual == true && CisRight) printf("ctverec\n");
    else if (CisEqual) printf("kosoctverec\n");
    else if (CisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    return 0;
}
