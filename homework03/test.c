#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//long long findRadix      ( long long   x )
//{
//}
//int       countZeros     ( long long   x )
//{
//}
//bool      findRadixZeros ( long long   x,
//                           long long * radix,
//                           int       * zeros )
//{
//}

int isValid(long long x) {
  return x > 1;
}

long long findRadix (long long x) {

  if (!isValid(x)) return -1;

  long long targetBase = 2;

  long long number = x;
  int currentCount = 0;
  int highestCount = 0;
  long long base = 2;
  while (base <= x) {
    //printf("\n<<base = %lld\nx = %lld>>\n\n", base, x);
    number = x;
    while (1) {
      //printf("count = %d\nnumber = %lld\n", currentCount, number);
      if (number % base == 0) currentCount++;
      if (number % base != 0) {
         //if (currentCount >= highestCount) { targetBase = base; printf("I like my cheeze moldy\n"); }
         if (currentCount >= highestCount) { targetBase = base; highestCount = currentCount;}
         number = x;
         base++;
         currentCount = 0;
         break;
      }
      number /= base;
    }
  }
  return targetBase;
}

int countZeros(long long x) {

  if (!isValid(x)) return -1;

  long long number = x;
  int currentCount = 0;
  int highestCount = 0;
  long long base = 2;
  while (base <= x) {
    //printf("\n<<base = %lld\nx = %lld>>\n\n", base, x);
    number = x;
    while (1) {
      //printf("count = %d\nnumber = %lld\n", currentCount, number);
      if (number % base == 0) currentCount++;
      if (number % base != 0) {
         //if (currentCount >= highestCount) { highestCount = currentCount; printf("I like my cheeze moldy\n"); }
         if (currentCount >= highestCount) highestCount = currentCount;
         number = x;
         base++;
         currentCount = 0;
         break;
      }
      number /= base;
    }
  }
  return highestCount;
}

bool findRadixZeros (long long x, long long *radix, int *zeros) {

  *radix = findRadix(x);

  *zeros = countZeros(x);

  if (*radix == -1 || *zeros == -1) { return 0; }

  return 1;
}

#ifndef __PROGTEST__
int       main ()
{
  
  long long radix;
  int       zeros;
  assert ( findRadix ( 2 ) == 2 );
  assert ( countZeros ( 2 ) == 1 );
  assert ( findRadixZeros ( 2, &radix, &zeros )
           && radix == 2
           && zeros == 1 );
  assert ( findRadix ( 16 ) == 2 );
  assert ( countZeros ( 16 ) == 4 );
  assert ( findRadixZeros ( 16, &radix, &zeros )
           && radix == 2
           && zeros == 4 );
  assert ( findRadix ( 17 ) == 17 );
  assert ( countZeros ( 17 ) == 1 );
  assert ( findRadixZeros ( 17, &radix, &zeros )
           && radix == 17
           && zeros == 1 );
  assert ( findRadix ( 36 ) == 6 );
  assert ( countZeros ( 36 ) == 2 );
  assert ( findRadixZeros ( 36, &radix, &zeros )
           && radix == 6
           && zeros == 2 );
  assert ( findRadix ( 100 ) == 10 );
  assert ( countZeros ( 100 ) == 2 );
  assert ( findRadixZeros ( 100, &radix, &zeros )
           && radix == 10
           && zeros == 2 );
  assert ( findRadix ( 216 ) == 6 );
  assert ( countZeros ( 216 ) == 3 );
  assert ( findRadixZeros ( 216, &radix, &zeros )
           && radix == 6
           && zeros == 3 );
  assert ( findRadix ( 343 ) == 7 );
  assert ( countZeros ( 343 ) == 3 );
  assert ( findRadixZeros ( 343, &radix, &zeros )
           && radix == 7
           && zeros == 3 );
  assert ( findRadix ( 1024 ) == 2 );
  assert ( countZeros ( 1024 ) == 10 );
  assert ( findRadixZeros ( 1024, &radix, &zeros )
           && radix == 2
           && zeros == 10 );
  assert ( findRadix ( 1296 ) == 6 );
  assert ( countZeros ( 1296 ) == 4 );
  assert ( findRadixZeros ( 1296, &radix, &zeros )
           && radix == 6
           && zeros == 4 );
  assert ( findRadix ( -8 ) == -1 );
  assert ( countZeros ( -8 ) == -1 );
  assert ( ! findRadixZeros ( -8, &radix, &zeros ) );
  return EXIT_SUCCESS;
}
  
  
  /*
  printf("findRadix(16) = %lld\n", findRadix(16));
  printf("countZeros(16) = %d\n", countZeros(16));
  printf("findRadix(216) = %lld\n", findRadix(216));
  printf("countZeros(216) = %d\n", countZeros(216));
  */

  // findRadix given tests
  /*
  assert ( findRadix ( 2 ) == 2 );
  assert ( findRadix ( 16 ) == 2 );
  assert ( findRadix ( 17 ) == 17 );
  assert ( findRadix ( 36 ) == 6 );
  assert ( findRadix ( 100 ) == 10 );
  assert ( findRadix ( 216 ) == 6 );
  assert ( findRadix ( 343 ) == 7 );
  assert ( findRadix ( 1024 ) == 2 );
  assert ( findRadix ( 1296 ) == 6 );
  assert ( findRadix ( -8 ) == -1 );
  */

  // countZeros given tests
  /*
  assert ( countZeros ( 2 ) == 1 );
  assert ( countZeros ( 16 ) == 4 );
  assert ( countZeros ( 17 ) == 1 );
  assert ( countZeros ( 36 ) == 2 );
  assert ( countZeros ( 100 ) == 2 );
  assert ( countZeros ( 216 ) == 3 );
  assert ( countZeros ( 343 ) == 3 );
  assert ( countZeros ( 1024 ) == 10 );
  assert ( countZeros ( 1296 ) == 4 );
  assert ( countZeros ( -8 ) == -1 );
  */

  //return 0;
//}
#endif /* __PROGTEST__ */
