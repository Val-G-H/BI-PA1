#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <stdint.h> // For int64_t
#include <stdlib.h> // Include this header for llabs
#include <inttypes.h> // For PRId64

// Union for extracting integer representation of a doubleи
union Double_t {
    double d;
    int64_t i;
};

bool eq(double a, double b) {
    const double epsilon = DBL_EPSILON; // Use the defined epsilon value
    const double abs_epsilon = 1e-15; // Absolute epsilon for very small numbers
    const int maxUlpsDiff = 4; // Define a threshold for ULP comparison

    printf("Comparing %.20f and %.20f\n", a, b);

    // Check for NaN
    if (isnan(a) || isnan(b)) {
        printf("One of the numbers is NaN\n");
        return false;
    }

    // Check for infinity
    if (isinf(a) || isinf(b)) {
        printf("One of the numbers is infinity\n");
        return a == b;
    }

    // Handle negative zero
    if (a == 0.0 && b == 0.0) {
        printf("Both numbers are zero\n");
        return true;
    }

    // Check for subnormal numbers
    if ((fabs(a) < DBL_MIN && a != 0.0) || (fabs(b) < DBL_MIN && b != 0.0)) {
        printf("One of the numbers is subnormal\n");
        return false;
    }

    // Check absolute difference
    double abs_diff = fabs(a - b);
    if (abs_diff < abs_epsilon) {
        printf("Absolute difference %e is less than abs_epsilon %e\n", abs_diff, abs_epsilon);
        return true;
    }

    // Scaled epsilon comparison
    double maxVal = fmax(fabs(a), fabs(b));
    double scaled_epsilon = epsilon * maxVal;
    if (abs_diff < scaled_epsilon) {
        printf("Absolute difference %e is less than scaled_epsilon %e\n", abs_diff, scaled_epsilon);
        return true;
    }

    // ULP comparison
    
    union Double_t uA = { .d = a };
    union Double_t uB = { .d = b };
    if ((uA.i < 0) != (uB.i < 0)) {
        printf("Numbers have different signs\n");
        return false;
    }
    int64_t ulpsDiff = llabs(uA.i - uB.i);
    if (ulpsDiff <= maxUlpsDiff) {
        printf("ULP difference %" PRId64 " is less than or equal to maxUlpsDiff %d\n", ulpsDiff, maxUlpsDiff);
        return true;
    }
    

    printf("Numbers are not approximately equal: abs_diff=%e, scaled_epsilon=%e, ulpsDiff=%" PRId64 "\n", abs_diff, scaled_epsilon, ulpsDiff);
    return false;
}

typedef struct {
    int test_number;
    double a;
    double b;
    const char *description;
    int expected_result;
} TestCase;

void run_tests() {
    // Test cases
    TestCase test_cases[] = {
        {1, 0.0, 0.0, "Both values are zero", 1},
        {2, -0.0, 0.0, "Negative zero and zero", 1},
        {3, 1.0, 1.0, "Both values are one", 1},
        {4, 1.0, 1.0 + DBL_EPSILON, "One and one plus epsilon", 1},
        {5, 1.0, 1.0 + 2 * DBL_EPSILON, "One and one plus two epsilon", 1},
        {6, 1.0, 1.0 + 10 * DBL_EPSILON, "One and one plus ten epsilon", 0},
        {7, 1e-10, 1e-10 + 1e-15, "Small numbers close to each other", 1},
        {8, 1e-10, 1e-10 + 1e-9, "Small numbers not close to each other", 0},
        {9, 1e10, 1e10 + 1e5, "Large numbers close to each other", 0},
        {10, 1e10, 1e10 + 1e7, "Large numbers not close to each other", 0},
        {11, DBL_MAX, DBL_MAX, "Both values are DBL_MAX", 1},
        {12, DBL_MAX, INFINITY, "DBL_MAX and infinity", 0},
        {13, INFINITY, INFINITY, "Both values are infinity", 1},
        {14, -INFINITY, -INFINITY, "Both values are negative infinity", 1},
        {15, INFINITY, -INFINITY, "Positive and negative infinity", 0},
        {16, NAN, NAN, "Both values are NaN", 0},
        {17, 0.1, 0.1, "Both values are 0.1", 1},
        {18, 0.1, 0.1 + DBL_EPSILON, "0.1 and 0.1 plus epsilon", 1},
        {19, 0.1, 0.1 + 1e-10, "0.1 and 0.1 plus 1e-10", 0},
        {20, 1.0, 1.0000000000000002, "One and one plus a very small number", 1},
        {21, 1.0, 1.000000000000002, "One and one plus a small number", 0},
        {22, 1.0, 1.0 + 4 * DBL_EPSILON, "One and one plus four epsilon", 1},
        {23, 1.0, 1.0 + 5 * DBL_EPSILON, "One and one plus five epsilon", 0},
        {24, 1.0, 1.0 + 1e-16, "One and one plus a very small amount", 1}, // Very Small Differences
        {25, -1.0, -1.0 - DBL_EPSILON, "Negative one and negative one minus epsilon", 1}, // Negative Numbers
        {26, 1.0, -1.0, "Positive one and negative one", 0}, // Mixed Signs
        {27, DBL_MIN / 2, DBL_MIN / 2 + DBL_MIN / 4, "Subnormal numbers close to each other", 1}, // Subnormal Numbers
        {28, 0.0, DBL_MIN / 2, "Zero and subnormal number", 0}, // Zero and Subnormal
        {29, 1.0, 2.0, "One and two", 0}, // Large Differences
        {30, 1.0, 1.0 + DBL_EPSILON / 2, "One and one plus half epsilon", 1}, // Precision Limits
        {31, DBL_MAX, INFINITY, "DBL_MAX and infinity", 0}, // Infinity and Large Numbers
        {32, NAN, 1.0, "NaN and one", 0}, // NaN Comparisons
        {33, -DBL_MAX, -INFINITY, "Negative DBL_MAX and negative infinity", 0}, // Negative Infinity
        {34, 1e-308, 1e-308 + 1e-320, "Very small numbers close to zero", 1}, // Close to Zero
        {35, 1e-10, 1e10, "Very small number and very large number", 0}, // Different Magnitudes
        {36, DBL_MIN, DBL_MIN + DBL_EPSILON, "DBL_MIN and DBL_MIN plus epsilon", 1}, // Boundary Values
        {37, -0.0, 0.0, "Negative zero and positive zero", 1}, // Negative Zero and Positive Zero
        {38, ((340.090 - 740.865) * (1241.872 - 887.560) + (1095.177 - 740.865) * (1288.335 - 887.560)), 0, "#7 test failing calculation, dot product calculation compared to 0", 1},
    };
    int num_tests = sizeof(test_cases) / sizeof(TestCase);
    for (int i = 0; i < num_tests; i++) {
        TestCase tc = test_cases[i];
        printf("\nTest %d: %s\n", tc.test_number, tc.description);
        int result = eq(tc.a, tc.b);
        if (result == tc.expected_result) {
            printf("Test passed: The values are %s.\n", result ? "approximately equal" : "not equal");
        } else {
            printf("\033[31mTest failed: Expected %s but got %s.\033[0m\n",
                   tc.expected_result ? "approximately equal" : "not equal",
                   result ? "approximately equal" : "not equal");
        }
    }
}

int main() {
    run_tests();
    return 0;
}