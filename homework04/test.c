#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
constexpr int SUITE_SPADES   = 0x000;
constexpr int SUITE_HEARTS   = 0x080;
constexpr int SUITE_CLUBS    = 0x100;
constexpr int SUITE_DIAMONDS = 0x180;

constexpr int SUITE_MASK = 0x180;
constexpr int VALUE_MASK = 0x07F;

constexpr int HAND_SIZE = 5;

constexpr int RES_DRAW       = 0;
constexpr int RES_WIN_A      = 1;
constexpr int RES_WIN_B      = -1;
constexpr int RES_INVALID    = 2;

#define SPADES(X)        ((X) | SUITE_SPADES)
#define HEARTS(X)        ((X) | SUITE_HEARTS)
#define CLUBS(X)         ((X) | SUITE_CLUBS)
#define DIAMONDS(X)      ((X) | SUITE_DIAMONDS)

#endif /* __PROGTEST__ */

// Extracts the value of a card
int getCardValue(int card) {
    return card & VALUE_MASK;
}

// Extracts the suite of a card
int getCardSuite(int card) {
    return card & SUITE_MASK;
}

// Verifies if a card is valid (proper suite + proper value)
int isValidCard (int card) {
  int value = getCardValue(card);
  //printf("Verifying card %x + %c\n\n", suite, value);
  if ((value >= '2' && value <= '9') || value == 'A' || value == 'K' || value == 'Q' || value == 'J' || value == 'X') {
    //printf("Value verification passed\n");
    return 1;    
  }
  //printf("Value verification failed\n");
  return 0;
}

int verifyHand ( const int playerA[]) {
  for (int i = 0; i < HAND_SIZE; i++) {
    if(!isValidCard(playerA[i])) return 0;
  }
  return 1;
}

int checkForDuplicates ( const int playerA[], const int playerB[] ) {

  // Check duplicates across player A and B
  for (int i = 0; i < HAND_SIZE; i++) {
    //printf("Comparing %x to hand of player B...\n", playerA[i]);
    for (int j = 0; j < HAND_SIZE; j++) {
      //printf("%x == %x is %d\n", playerA[i], playerB[j], playerA[i] == playerB[j]);
      if (playerA[i] == playerB[j]) {
        //printf("Duplicate found.\nplayerA[%d] = %x + %c\nplayerB[%d] = %x + %c\n", i, getCardSuite(playerA[i]), getCardValue(playerA[i]), j, getCardSuite(playerB[j]), getCardValue(playerB[j]));
        return 1;
      }
    }  
  }

  // Check duplicates on player A
  for (int i = 0; i < HAND_SIZE; i++) {
    for (int j = 0; j < HAND_SIZE; j++) {
      if (playerA[i] == playerA[j] && i != j) {
        return 1;
      }
    }  
  }

  // Check duplicates on player B
  for (int i = 0; i < HAND_SIZE; i++) {
    for (int j = 0; j < HAND_SIZE; j++) {
      if (playerB[i] == playerB[j] && i != j) {
        return 1;
      }
    }  
  }

  return 0;
}

int isSameSuit(const int hand[]) {
    int suit = getCardSuite(hand[0]);
    for (int i = 1; i < 5; ++i) {
        if (getCardSuite(hand[i]) != suit)
            return 0;
    }
    return 1;
}

int cardValueToRank(int value) {
    if (value >= '2' && value <= '9')
        return value - '0'; // '2' to '9' -> 2 to 9
    switch (value) {
        case 'X': return 10; // 10
        case 'J': return 11; // Jack
        case 'Q': return 12; // Queen
        case 'K': return 13; // King
        case 'A': return 14; // Ace
        default: return -1;  // Invalid card value, shouldn't happen though as we validate every value with isValidCard before proceeding any further
    }
}

void sortAscendingValues ( int hand[] ) {

  for (int i = 0; i < HAND_SIZE; ++i) {
        for (int j = i + 1; j < HAND_SIZE; ++j) {
            if (hand[i] > hand[j]) {
                int temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
        }
    }

}

// Check if the sorted card values form a consecutive sequence
int isConsecutive(int hand[]) {
    for (int i = 0; i < 4; ++i) {
        if (hand[i] + 1 != hand[i + 1])
            return 0;
    }
    return 1;
}

// Main function to check for a straight flush
int isStraightFlush(const int hand[]) {
    if (!isSameSuit(hand))
        return 0;

    int values[5];
    for (int i = 0; i < 5; ++i) {
        values[i] = cardValueToRank(getCardValue(hand[i]));
        if (values[i] == -1)
            return 0; // Invalid card value
    }

    // Sort values to check if they are consecutive
    sortAscendingValues(values);

    return isConsecutive(values);
}

int getHighestValue( const int hand[]) {

  int values[5];
  for (int i = 0; i < 5; ++i) {
    values[i] = cardValueToRank(getCardValue(hand[i]));
  }
    
  sortAscendingValues(values);
  return values[4]; // The highest card after sorting

}

int comparePokerHands ( const int playerA[], const int playerB[] )
{
  // Verify all cards to be valid
  if (verifyHand(playerA) == 0) return RES_INVALID;
  if (verifyHand(playerB) == 0) return RES_INVALID;

  // Check for duplicates
  if (checkForDuplicates(playerA, playerB)) return RES_INVALID;


  // Straight Flush
  if (isStraightFlush(playerA) && isStraightFlush(playerB)) {
    if (getHighestValue(playerA) > getHighestValue(playerB)) return RES_WIN_A;
    else if (getHighestValue(playerA) < getHighestValue(playerB)) return RES_WIN_B;
    else return RES_DRAW;
  }
  if (isStraightFlush(playerA)) return RES_WIN_A;
  if (isStraightFlush(playerB)) return RES_WIN_B;


  // 4-of-kind

  // Full House

  // Flush

  // Straight

  // 3-of-kind 


  // Two Pair

  // One Pair

  // Nothing

  return 69;
}

void printHand (const int hand[]) {
  printf("\n[Printing a hand]\n");
  for (int i = 0; i < HAND_SIZE; i++) {
    printf("%x + %c\n", getCardSuite(hand[i]), getCardValue(hand[i]));
  }
}

#ifndef __PROGTEST__
int main ()
{

  int straightFlush1[] = { CLUBS('J'), CLUBS('X'), CLUBS('9'), CLUBS('8'), CLUBS('7')};
  assert ( isStraightFlush(straightFlush1) == 1 );

  int straightFlush2[] = { HEARTS('A'), HEARTS('J'), HEARTS('Q'), HEARTS('K'), HEARTS('X')};
  assert ( isStraightFlush(straightFlush2) == 1 );

  int straightFlush3[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  assert ( isStraightFlush(straightFlush3) == 0 );

  int straightFlush4[] = { DIAMONDS('A'), DIAMONDS('J'), DIAMONDS('Q'), DIAMONDS('K'), DIAMONDS('X')};
  assert ( isStraightFlush(straightFlush4) == 1 ); 

  assert (comparePokerHands(straightFlush1, straightFlush2) == RES_WIN_B);
  assert (comparePokerHands(straightFlush2, straightFlush4) == RES_DRAW);
  assert (comparePokerHands(straightFlush4, straightFlush1) == RES_WIN_A);

  assert (isValidCard(SPADES('B')) == 0);
  assert (isValidCard(HEARTS('2')) == 1);
  assert (isValidCard(420) == 0);

  int x13[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y13[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), HEARTS('5'), HEARTS('4') };
  assert ( comparePokerHands ( x13, y13 ) == RES_INVALID );

  int x14[] = { DIAMONDS('A'), HEARTS('Z'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y14[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x14, y14 ) == RES_INVALID );

  int x15[] = { DIAMONDS('A'), HEARTS('2'), SPADES('4'), DIAMONDS('A'), CLUBS('4') };
  int y15[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x15, y15 ) == RES_INVALID );

  int x16[] = { DIAMONDS('A'), HEARTS('2'), SPADES('4'), DIAMONDS('X'), CLUBS('4') };
  int y16[] = { DIAMONDS('4'), DIAMONDS('4'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x16, y16 ) == RES_INVALID );


  return 0;

  /*

  int x0[] = { SPADES('5'), HEARTS('5'), CLUBS('5'), DIAMONDS('5'), HEARTS('X') };
  int y0[] = { SPADES('6'), SPADES('9'), SPADES('8'), SPADES('X'), SPADES('7') };
  assert ( comparePokerHands ( x0, y0 ) == RES_WIN_B );

  int x1[] = { SPADES('2'), HEARTS('2'), CLUBS('2'), SPADES('A'), DIAMONDS('2') };
  int y1[] = { CLUBS('A'), HEARTS('K'), HEARTS('A'), SPADES('K'), DIAMONDS('A') };
  assert ( comparePokerHands ( x1, y1 ) == RES_WIN_A );

  int x2[] = { CLUBS('3'), HEARTS('2'), HEARTS('3'), SPADES('2'), DIAMONDS('3') };
  int y2[] = { CLUBS('A'), CLUBS('9'), CLUBS('Q'), CLUBS('4'), CLUBS('J') };
  assert ( comparePokerHands ( x2, y2 ) == RES_WIN_A );

  int x3[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y3[] = { CLUBS('2'), CLUBS('4'), CLUBS('6'), CLUBS('3'), CLUBS('X') };
  assert ( comparePokerHands ( x3, y3 ) == RES_WIN_B );

  int x4[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y4[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x4, y4 ) == RES_WIN_A );

  int x5[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y5[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x5, y5 ) == RES_WIN_B );

  int x6[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y6[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x6, y6 ) == RES_WIN_A );

  int x7[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y7[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x7, y7 ) == RES_WIN_B );

  int x8[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y8[] = { CLUBS('Q'), DIAMONDS('K'), CLUBS('2'), CLUBS('A'), HEARTS('3') };
  assert ( comparePokerHands ( x8, y8 ) == RES_WIN_B );

  int x9[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y9[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x9, y9 ) == RES_WIN_A );

  int x10[] = { CLUBS('A'), CLUBS('2'), CLUBS('3'), CLUBS('4'), CLUBS('5') };
  int y10[] = { HEARTS('J'), CLUBS('J'), SPADES('J'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x10, y10 ) == RES_WIN_B );

  int x11[] = { CLUBS('A'), CLUBS('K'), CLUBS('Q'), CLUBS('J'), CLUBS('X') };
  int y11[] = { HEARTS('3'), CLUBS('3'), SPADES('3'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x11, y11 ) == RES_WIN_A );

  int x12[] = { CLUBS('A'), HEARTS('A'), CLUBS('Q'), HEARTS('Q'), CLUBS('J') };
  int y12[] = { SPADES('A'), DIAMONDS('A'), SPADES('Q'), DIAMONDS('Q'), SPADES('J') };
  assert ( comparePokerHands ( x12, y12 ) == RES_DRAW );

  int x13[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y13[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), HEARTS('5'), HEARTS('4') };
  assert ( comparePokerHands ( x13, y13 ) == RES_INVALID );

  int x14[] = { DIAMONDS('A'), HEARTS('Z'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y14[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x14, y14 ) == RES_INVALID );

  return EXIT_SUCCESS;
  */
}
#endif /* __PROGTEST__ */

