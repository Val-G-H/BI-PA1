#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

struct Point {
    double x, y;
};

bool eq(double left, double right) {
    double epsilon = DBL_EPSILON * fmax(fabs(left), fabs(right));
    if (fabs(left - right) != 0) {
        printf("%.16lf <= %.16lf (%.16lf * %.16lf): %d\n", fabs(left - right), epsilon, DBL_EPSILON, fmax(fabs(left), fabs(right)), fabs(left - right) <= epsilon ? 1 : 0);        
    }
    return fabs(left - right) <= epsilon;
}

double vectorDotProduct(struct Point a, struct Point b, struct Point c, struct Point d) {
    return (b.x - a.x) * (b.y - a.y) + (d.x - c.x) * (d.y - c.y);
}

double vectorLength(struct Point a, struct Point b) {
    return sqrt( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) );
}

int test_scan(char *test_case, char *bodA, char *bodB, char *bodC, char *notification, char *bodAn, char *bodBn, char *bodCn) {
    printf("=== %s =====================================================================\n", test_case);

    struct Point a, b, c;
    char closingBracket = '\0';

    // input for A
    printf("Bod A: %s\n", bodA);
    int conversions = sscanf(bodA," [ %lf , %lf %c", &(a.x), &(a.y), &closingBracket);
    if (conversions != 3) {
        if (strlen(notification) != 0) {
            printf("%s - expected\n", notification);            
        }    
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';

    // input for B
    printf("Bod B: %s\n", bodB);
    conversions = sscanf(bodB, " [ %lf , %lf %c", &(b.x), &(b.y), &closingBracket);
    if (conversions != 3) {
        if (strlen(notification) != 0) {
            printf("%s - expected\n", notification);
        }    
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';
    
    // input for C
    printf("Bod C: %s\n", bodC);
    conversions = sscanf(bodC, " [ %lf , %lf %c", &(c.x), &(c.y), &closingBracket);
    if (conversions != 3) {
        if (strlen(notification) != 0) {
            printf("%s - expected\n", notification);
        }    
        printf("Nespravny vstup.\n");
        return 1;
    }
    closingBracket = '\0';

    if (strlen(notification) != 0) {
        printf("%s - expected\n", notification);
    }    
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

    // all sides are equal if two touching sides are equal
    if(eq(ab, newAb)) AisEqual = true;
    if(eq(ab, aNewB)) BisEqual = true;
    if(eq(ac, aNewC)) CisEqual = true;

    printf("A': %s - expected\n", bodAn);
    printf("A': [%g,%g], ", newA.x, newA.y);
    if (AisEqual == true && AisRight) printf("ctverec\n");
    else if (AisEqual) printf("kosoctverec\n");
    else if (AisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    printf("B': %s - expected\n", bodBn);
    printf("B': [%g,%g], ", newB.x, newB.y);
    if (BisEqual == true && BisRight) printf("ctverec\n");
    else if (BisEqual) printf("kosoctverec\n");
    else if (BisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    printf("C': %s - expected\n", bodCn);
    printf("C': [%g,%g], ", newC.x, newC.y);
    if (CisEqual == true && CisRight) printf("ctverec\n");
    else if (CisEqual) printf("kosoctverec\n");
    else if (CisRight) printf("obdelnik\n");
    else printf("rovnobeznik\n");

    return 0;
}

int main() {
    test_scan("1", "[0, 0]", "[7, 0]", "[3, 2]",
        "", "[10,2], rovnobeznik", "[-4,2], rovnobeznik", "[4,-2], rovnobeznik");
    test_scan("2", "[0,0]", "[  5  ,  0     ]", "\n\n\n\n[3, \n4\n]",
        "", "[8,4], kosoctverec", "[-2,4], rovnobeznik", "[2,-4], rovnobeznik");
    test_scan("3", "[0,0]", "[-3,4]", "[4,3]",
        "", "[1,7], ctverec", "[7,-1], rovnobeznik", "[-7,1], rovnobeznik");
    test_scan("4", "[10.5, 10.5]", "[12.5, 10.5]", "[10.5, 15e+0]",
        "", "[12.5,15], obdelnik", "[8.5,15], rovnobeznik", "[12.5,6], rovnobeznik");
    test_scan("5", "[0, 0]", "[3, 3]", "[10, 10]",
        "Rovnobezniky nelze sestrojit.", "", "", "");
    test_scan("6", "[0, 0]", "[2270.242, 0]", "[234.08, 2258.142]",
        "", "[2504.322,2258.142], kosoctverec", "[-2036.162,2258.142], rovnobeznik", "[2036.162,-2258.142], rovnobeznik");
    test_scan("7", "[740.865, 887.560]", "[340.090, 1241.872]", "[1095.177, 1288.335]",
        "", "[694.402,1642.647], ctverec", "[1495.952,934.023], rovnobeznik", "[-14.222,841.097], rovnobeznik");            
    test_scan("8", "[-306.710, -894.018]", "[6369.015, 66159.129]", "[6016.590, 62619.258]",
        "Rovnobezniky nelze sestrojit.", "", "", "");
    test_scan("9", "[2, 5]", "[3, abcd]", "",
        "Nespravny vstup.", "", "", "");
    test_scan("10", "[2, 5]", "[3, 4]", "[7 9]",
        "Nespravny vstup.", "", "", "");

    return 0;
}