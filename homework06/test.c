#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#endif  /* __PROGTEST__ */

typedef struct {
    char *data;       // integer array
    size_t size;     // current element count
    size_t capacity; // potential storage
} DynamicArray;

DynamicArray createArray(size_t initialCapacity) {
    DynamicArray arr;
    arr.data = (char *)malloc(initialCapacity * sizeof(char));
    if (arr.data == NULL) {
        //fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    arr.size = 0;
    arr.capacity = initialCapacity;
    return arr;
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void append(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        // Zvýšení kapacity pole na dvojnásobek
        arr->capacity *= 2;
        char *newData = (char *)realloc(arr->data, arr->capacity * sizeof(char));
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
        printf("%c ", arr->data[i]);
    }
    printf("\n");
}

char *intToRoman(int num) {
    static const struct {
        int value;
        const char *symbol;
    } romanSymbols[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    char *roman = (char *)malloc(20 * sizeof(char)); // Max délka pro 3999 je 15 znaků
    if (!roman) exit(1);
    roman[0] = '\0';

    for (size_t i = 0; i < sizeof(romanSymbols) / sizeof(romanSymbols[0]); i++) {
        while (num >= romanSymbols[i].value) {
            strcat(roman, romanSymbols[i].symbol);
            num -= romanSymbols[i].value;
        }
    }
    return roman;
}

int isDelimiter(char c) {
    return isspace(c) || ispunct(c) || c == '\0';
}

char *arabicToRoman(const char *str) {
    DynamicArray result = createArray(strlen(str)); // Pro dynamické budování výsledného textu
    size_t len = strlen(str);
    size_t start = 0;

    while (start < len) {
        // Zkopírujeme znaky, které nejsou čísla
        while (start < len && !isdigit(str[start])) {
            append(&result, str[start++]);
        }

        // Pokud začíná číslo, pokusíme se ho najít
        size_t end = start;
        while (end < len && isdigit(str[end])) {
            end++;
        }

        // Zpracování čísla, pokud je odděleno oddělovači
        if (start < len && (start == 0 || isDelimiter(str[start - 1])) && (end == len || isDelimiter(str[end]))) {
            char buffer[20];
            strncpy(buffer, str + start, end - start);
            buffer[end - start] = '\0';

            int number = atoi(buffer);
            if (number >= 1 && number <= 3999) {
                char *roman = intToRoman(number);
                for (size_t i = 0; roman[i] != '\0'; i++) {
                    append(&result, roman[i]);
                }
                free(roman);
            } else {
                for (size_t i = start; i < end; i++) {
                    append(&result, str[i]); // Neplatné číslo zkopírujeme
                }
            }
        } else if (start < len) {
            // Číslo není odděleno, zkopírujeme ho
            for (size_t i = start; i < end; i++) {
                append(&result, str[i]);
            }
        }

        start = end;
    }

    // Převod dynamického pole zpět na řetězec
    char *finalResult = (char *)malloc((result.size + 1) * sizeof(char));
    if (!finalResult) exit(1);
    memcpy(finalResult, result.data, result.size * sizeof(char));
    finalResult[result.size] = '\0';

    freeArray(&result);
    return finalResult;
}



#ifndef __PROGTEST__

int tests() {
char * r;

  r = arabicToRoman ( "CVUT FIT was founded on July 1-st 2009" );
  assert ( ! strcmp ( r, "CVUT FIT was founded on July I-st MMIX" ) );
  free ( r );

  r = arabicToRoman ( "PA1 is my favorite subject, rating 5 out of 5stars" );
  printf("%s\n", r);
  assert ( ! strcmp ( r, "PA1 is my favorite subject, rating V out of 5stars" ) );
  free ( r );

  r = arabicToRoman ( "The range of int data type is -2147483648 to 2147483647 inclusive." );
  assert ( ! strcmp ( r, "The range of int data type is -2147483648 to 2147483647 inclusive." ) );
  free ( r );

  r = arabicToRoman ( "There are 11 integers in closed interval 10-20" );
  assert ( ! strcmp ( r, "There are XI integers in closed interval X-XX" ) );
  free ( r );

  r = arabicToRoman ( "Chuck Norris and agent 007 are able to solve all Progtest homework problems on the 1-st try" );
  assert ( ! strcmp ( r, "Chuck Norris and agent VII are able to solve all Progtest homework problems on the I-st try" ) );
  free ( r );

  return 1;
  
}

int main ()
{
  tests();

  //char * r;

  //r = "CVUT FIT was founded on July 1-st 2009";
  //char * r_processed = arabicToRoman(r);
}
#endif  /* __PROGTEST__ */
