#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct {
    int *data;       // integer array
    size_t size;     // current element count
    size_t capacity; // potential storage
} DynamicArray;

// Funkce pro vytvoření prázdného pole
DynamicArray createArray(size_t initialCapacity) {
    DynamicArray arr;
    arr.data = (int *)malloc(initialCapacity * sizeof(int));
    if (arr.data == NULL) {
        //fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    arr.size = 0;
    arr.capacity = initialCapacity;
    return arr;
}

// Funkce pro uvolnění paměti pole
void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

// Funkce pro přidání prvku do pole
void append(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        // Zvýšení kapacity pole na dvojnásobek
        arr->capacity *= 2;
        int *newData = (int *)realloc(arr->data, arr->capacity * sizeof(int));
        if (newData == NULL) {
            //fprintf(stderr, "Error: Memory reallocation failed\n");
            exit(1);
        }
        arr->data = newData;
    }
    arr->data[arr->size++] = value;
}

void printArray(const DynamicArray *arr) {
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

int readRows(DynamicArray *arr) {
    int num;
    char ch;
    int expectingDigit = 0;

    printf("Pocty pruhu:\n");

    // Read characters until EOF
    while ((ch = getchar()) != EOF) {
        if (ch == '{') {
            // Start of input
            expectingDigit = 1;
        } else if (isdigit(ch) && !expectingDigit) {
            return 0;
        } else if (isdigit(ch)) {
            ungetc(ch, stdin);
            if (scanf("%d", &num) != 1 || num <= 0) {
                //fprintf(stderr, "Invalid input: only positive integers are allowed.\n");
                return 0;
            }
            append(arr, num);
            expectingDigit = 0; // Reset for next comma or closing brace
        } else if (ch == ',' && !expectingDigit) {
            expectingDigit = 1; // Indicate that a number should come next
        } else if (ch == '}' && !expectingDigit) {
            return 1; // Successfully finished reading input
        } else if (!isspace(ch)) {
            //fprintf(stderr, "Invalid input format.\n");
            return 0; // Invalid character or format
        }
    }

    // If we reach EOF without a closing brace
    //fprintf(stderr, "Invalid input: missing closing brace.\n");
    return 0;
}

// Funkce pro výpočet největšího společného dělitele (GCD)
long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        long long int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Funkce pro výpočet nejmenšího společného násobku (LCM)
long long int lcm(long long int a, long long int b) {
    return (a / gcd(a, b)) * b;
}

long long int calculateVehicles (size_t from, size_t to, const DynamicArray * arr) {
    long long int result = arr->data[from];
    for (size_t i = from + 1; i < to; i++) {
        result = lcm(result, arr->data[i]);
    }
    return result;
}

int readSegment(const DynamicArray* arr) {
    while (1) {
        size_t to, from;
        int conversions = scanf("%lu %lu", &from, &to);
        if (conversions == EOF) {
            return 1;
        }
        if (conversions != 2 || from >= to || from > arr->size || to > arr->size || to < 0 || from < 0) {
            return 0;
        }

        long long int result = calculateVehicles(from, to, arr);

        printf("Vozidel: %lld\n", result);
    }
}

int main() {
    DynamicArray roadRows = createArray(1);

    if (!readRows(&roadRows)) {
        puts("Nespravny vstup.");
        freeArray(&roadRows);
        return 1;
    }
    //printArray(&roadRows);

    printf("Trasy:\n");

    if (!readSegment(&roadRows)) {
        puts("Nespravny vstup.");
        freeArray(&roadRows);
        return 1;
    }

    //printf("\n");

    freeArray(&roadRows);
    return 0;
}