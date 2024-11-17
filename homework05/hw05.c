#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct {
    int *data;        
    size_t size;      
    size_t capacity;  
} DynamicArray;

// Funkce pro vytvoření prázdného pole
DynamicArray createArray(size_t initialCapacity) {
    DynamicArray arr;
    arr.data = (int *)malloc(initialCapacity * sizeof(int));
    if (arr.data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
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
            fprintf(stderr, "Error: Memory reallocation failed\n");
            exit(EXIT_FAILURE);
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

    // Read characters until EOF
    while ((ch = getchar()) != EOF) {
        if (ch == '{') {
            // Start of input
            expectingDigit = 1;
        } else if (isdigit(ch)) {
            ungetc(ch, stdin);
            if (scanf("%d", &num) != 1 || num <= 0) {
                fprintf(stderr, "Invalid input: only positive integers are allowed.\n");
                return 0;
            }
            append(arr, num);
            expectingDigit = 0; // Reset for next comma or closing brace
        } else if (ch == ',' && !expectingDigit) {
            expectingDigit = 1; // Indicate that a number should come next
        } else if (ch == '}' && !expectingDigit) {
            return 1; // Successfully finished reading input
        } else if (!isspace(ch)) {
            fprintf(stderr, "Invalid input format.\n");
            return 0; // Invalid character or format
        }
    }

    // If we reach EOF without a closing brace
    fprintf(stderr, "Invalid input: missing closing brace.\n");
    return 0;
}

int main() {

    DynamicArray roadRows = createArray(1);

    if (!readRows(&roadRows)) {
        puts("womp womp");
    }
    

    printArray(&roadRows);

    freeArray(&roadRows);
    return 0;
}