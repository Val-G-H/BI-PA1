#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
constexpr int SUITE_SPADES   = 0x000;
constexpr int SUITE_HEARTS   = 0x080;
constexpr int SUITE_CLUBS    = 0x100;
constexpr int SUITE_DIAMONDS = 0x180;
constexpr int RES_DRAW       = 0;
constexpr int RES_WIN_A      = 1;
constexpr int RES_WIN_B      = -1;
constexpr int RES_INVALID    = 2;

#define SPADES(X)        ((X) | SUITE_SPADES)
#define HEARTS(X)        ((X) | SUITE_HEARTS)
#define CLUBS(X)         ((X) | SUITE_CLUBS)
#define DIAMONDS(X)      ((X) | SUITE_DIAMONDS)

#endif /* __PROGTEST__ */

// My constants
const int SUITE_MASK = 0x180;
const int VALUE_MASK = 0x07F;

const int HAND_SIZE = 5;



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

  if (card < 0 || card > 511) return 0;

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
        //printf("Duplicates found in player A hand.\n");
        return 1;
      }
    }  
  }

  // Check duplicates on player B
  for (int i = 0; i < HAND_SIZE; i++) {
    for (int j = 0; j < HAND_SIZE; j++) {
      if (playerB[i] == playerB[j] && i != j) {
        //printf("Duplicates found in player B hand.\n");
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

int getHighestValue( const int hand[]) {

  int values[5];
  for (int i = 0; i < 5; ++i) {
    values[i] = cardValueToRank(getCardValue(hand[i]));
  }
    
  sortAscendingValues(values);
  return values[4]; // The highest card after sorting

}

void countCardValues(const int hand[], int valueCount[]) {
  for (int i = 0; i < 5; ++i) {
    int value = cardValueToRank(getCardValue(hand[i]));
    if (value >= 2 && value <= 14) valueCount[value]++;
  }
}

int isStraight ( const int hand[]) {
  int values[5];
  for (int i = 0; i < 5; ++i) {
    values[i] = cardValueToRank(getCardValue(hand[i]));
    if (values[i] == -1) return -1; // Invalid card value
  }
  // Sort values to check if they are consecutive
  sortAscendingValues(values);

  return isConsecutive(values);
}

int isFlush(const int hand[]) {
  if (!isSameSuit(hand)) return 0;
  return 1;
}

// Main function to check for a straight flush
/*
int isStraightFlush(const int hand[]) {
  if (!isSameSuit(hand)) return 0;
  int values[5];
  for (int i = 0; i < 5; ++i) {
    values[i] = cardValueToRank(getCardValue(hand[i]));
    if (values[i] == -1) return 0; // Invalid card value
  }
  // Sort values to check if they are consecutive
  sortAscendingValues(values);

  return isConsecutive(values);
}
*/

int isStraightFlush(const int hand[]) {
  if (!isFlush(hand) || !isStraight(hand)) return 0;
  return 1;
}

int getFourOfKindValue(const int hand[]) {
    int valueCount[15] = {0}; // Index 2 to 14 for card ranks 2 to Ace
    countCardValues(hand, valueCount);

    for (int i = 14; i >= 2; --i) {
        if (valueCount[i] == 4) {
            return i; // Return the value of the four-of-a-kind
        }
    }
    return -1; // No four-of-a-kind found
}

int getThreeOfKindValue(const int hand[]) {
    int valueCount[15] = {0}; // Index 2 to 14 for card ranks 2 to Ace
    countCardValues(hand, valueCount);

    for (int i = 14; i >= 2; --i) {
        if (valueCount[i] == 3) {
            return i; // Return the value of the three-of-kind
        }
    }
    return -1; // No three-of-kind found
}

int isFourOfKind(const int hand[]) {
  if (getFourOfKindValue(hand) == -1) return 0;
  return 1;
}

int isThreeOfKind(const int hand[]) {
  if (getThreeOfKindValue(hand) == -1) return 0;
  return 1;
}

int getFullHouseValues(const int hand[]) {
  int valueCount[15] = {0}; // Index 2 to 14 for card ranks 2 to Ace
  countCardValues(hand, valueCount);

  int threeOfKindValue = -1;
  int pairValue = -1;

  for (int i = 14; i >= 2; --i) {
    if (valueCount[i] == 3 && threeOfKindValue == -1) {
      threeOfKindValue = i; // Record the three-of-a-kind value
    } else if (valueCount[i] == 2 && pairValue == -1) {
      pairValue = i; // Record the pair value
      }
  }

  if (threeOfKindValue != -1 && pairValue != -1) return threeOfKindValue; // Valid full house found
  return -1; // No full house found
}

int isFullHouse(const int hand[]) {
  if (getFullHouseValues(hand) != -1) return 1;
  return 0;
}



int flushTiebreaker(const int playerA[], const int playerB[]) {
  int handA[5];
  int handB[5];
  for (int i = 0; i < 5; ++i) {
    handA[i] = cardValueToRank(getCardValue(playerA[i]));
  }
  for (int i = 0; i < 5; ++i) {
    handB[i] = cardValueToRank(getCardValue(playerB[i]));
  }
  sortAscendingValues(handA);
  sortAscendingValues(handB);
  for (int i = 4; i > -1; i--) {
    if (handA[i] > handB[i]) return RES_WIN_A;
    if (handA[i] < handB[i]) return RES_WIN_B;
  }
  return RES_DRAW;
}

int isTwoPair(const int hand[]) {
    int valueCounts[15] = {0}; // Array to count occurrences of card values (2 to A)
    
    // Count the card values
    for (int i = 0; i < 5; ++i) {
      int value = cardValueToRank(getCardValue(hand[i]));
      valueCounts[value]++;
    }

    int pairCount = 0;

    // Collect the two pairs and the kicker
    for (int i = 14; i >= 2; --i) {
      if (valueCounts[i] == 2) {
        pairCount++;
        if (pairCount == 2) break; // Found both pairs
      }
    }

    if (pairCount == 2) {
      return 1; // Valid two pair
    }
    return 0; // Not a two pair
}

int isOnePair(const int hand[]) {
    int valueCounts[15] = {0}; // Array to count occurrences of card values (2 to A)
    
    // Count the card values
    for (int i = 0; i < 5; ++i) {
      int value = cardValueToRank(getCardValue(hand[i]));
      valueCounts[value]++;
    }

    int pairCount = 0;

    // Collect the two pairs and the kicker
    for (int i = 14; i >= 2; --i) {
      if (valueCounts[i] == 2) {
        pairCount++;
        if (pairCount == 1) break; // Found both pairs
      }
    }

    if (pairCount == 1) {
      return 1; // Valid one pair
    }
    return 0; // Not a two pair
}

int twoPairTiebreaker(const int playerA[], const int playerB[]) {
    int valueCountA[15] = {0}, valueCountB[15] = {0};
    countCardValues(playerA, valueCountA);
    countCardValues(playerB, valueCountB);

    int pairsA[2] = {-1, -1}, pairsB[2] = {-1, -1}, kickerA = -1, kickerB = -1;
    int pairIndexA = 0, pairIndexB = 0;

    // Extract pairs and kicker for Player A
    for (int i = 14; i >= 2; --i) {
        if (valueCountA[i] == 2) {
            pairsA[pairIndexA++] = i;
        } else if (valueCountA[i] == 1 && kickerA == -1) {
            kickerA = i;
        }
    }

    // Extract pairs and kicker for Player B
    for (int i = 14; i >= 2; --i) {
        if (valueCountB[i] == 2) {
            pairsB[pairIndexB++] = i;
        } else if (valueCountB[i] == 1 && kickerB == -1) {
            kickerB = i;
        }
    }

    // Compare highest pairs first
    if (pairsA[0] != pairsB[0]) return pairsA[0] > pairsB[0] ? RES_WIN_A : RES_WIN_B;
    // Compare second pairs
    if (pairsA[1] != pairsB[1]) return pairsA[1] > pairsB[1] ? RES_WIN_A : RES_WIN_B;
    // Compare kicker
    return kickerA != kickerB ? (kickerA > kickerB ? RES_WIN_A : RES_WIN_B) : RES_DRAW;
}

int onePairTiebreaker(const int playerA[], const int playerB[]) {
    int valueCountA[15] = {0}, valueCountB[15] = {0};
    countCardValues(playerA, valueCountA);
    countCardValues(playerB, valueCountB);

    int pairA = -1, pairB = -1;
    int kickersA[3] = {-1, -1, -1}, kickersB[3] = {-1, -1, -1};
    int kickerIndexA = 0, kickerIndexB = 0;

    // Find pair and kickers for Player A
    for (int i = 14; i >= 2; --i) {
        if (valueCountA[i] == 2) {
            pairA = i;
        } else if (valueCountA[i] == 1) {
            kickersA[kickerIndexA++] = i;
        }
    }

    // Find pair and kickers for Player B
    for (int i = 14; i >= 2; --i) {
        if (valueCountB[i] == 2) {
            pairB = i;
        } else if (valueCountB[i] == 1) {
            kickersB[kickerIndexB++] = i;
        }
    }

    // Compare pairs first
    if (pairA != pairB) return pairA > pairB ? RES_WIN_A : RES_WIN_B;

    // Compare kickers in descending order
    for (int i = 0; i < 3; ++i) {
        if (kickersA[i] != kickersB[i]) return kickersA[i] > kickersB[i] ? RES_WIN_A : RES_WIN_B;
    }

    return RES_DRAW;
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
  if (isFourOfKind(playerA) && isFourOfKind(playerB)) {
    if (getFourOfKindValue(playerA) > getFourOfKindValue(playerB)) return RES_WIN_A;
    else if (getFourOfKindValue(playerA) < getFourOfKindValue(playerB)) return RES_WIN_B;
    else return RES_DRAW;
  }
  if (isFourOfKind(playerA)) return RES_WIN_A;
  if (isFourOfKind(playerB)) return RES_WIN_B;

  // Full House
  if (isFullHouse(playerA) && isFullHouse(playerB)) {
    if (getThreeOfKindValue(playerA) > getThreeOfKindValue(playerB)) return RES_WIN_A;
    else if (getThreeOfKindValue(playerA) < getThreeOfKindValue(playerB)) return RES_WIN_B;
    else return RES_DRAW;
  }
  if (isFullHouse(playerA)) return RES_WIN_A;
  if (isFullHouse(playerB)) return RES_WIN_B;
  

  // Flush
  if (isFlush(playerA) && isFlush(playerB)) {
    return flushTiebreaker(playerA, playerB);
  }
  if (isFlush(playerA)) return RES_WIN_A;
  if (isFlush(playerB)) return RES_WIN_B;

  // Straight
  if (isStraight(playerA) && isStraight(playerB)) {
    if (getHighestValue(playerA) > getHighestValue(playerB)) return RES_WIN_A;
    else if (getHighestValue(playerA) < getHighestValue(playerB)) return RES_WIN_B;
    else return RES_DRAW;
  }
  if (isStraight(playerA)) return RES_WIN_A;
  if (isStraight(playerB)) return RES_WIN_B;
  

  // 3-of-kind 
  if (isThreeOfKind(playerA) && isThreeOfKind(playerB)) {
    if (getThreeOfKindValue(playerA) > getThreeOfKindValue(playerB)) return RES_WIN_A;
    else if (getThreeOfKindValue(playerA) < getThreeOfKindValue(playerB)) return RES_WIN_B;
    else return RES_DRAW;
  }
  if (isThreeOfKind(playerA)) return RES_WIN_A;
  if (isThreeOfKind(playerB)) return RES_WIN_B;

  // Two Pair
  if (isTwoPair(playerA) && isTwoPair(playerB)) return twoPairTiebreaker(playerA, playerB); 
  if (isTwoPair(playerA)) return RES_WIN_A;
  if (isTwoPair(playerB)) return RES_WIN_B;

  // One Pair
  if (isOnePair(playerA) && isOnePair(playerB)) return onePairTiebreaker(playerA, playerB);
  if (isOnePair(playerA)) return RES_WIN_A;
  if (isOnePair(playerB)) return RES_WIN_B;

  // Nothing
  return flushTiebreaker(playerA, playerB);

  return RES_DRAW;
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

  // Verify all cards to be valid
  assert ( isValidCard(SPADES('2') ) == 1 );
  assert ( isValidCard(SPADES('3') ) == 1 );
  assert ( isValidCard(SPADES('4') ) == 1 );
  assert ( isValidCard(SPADES('5') ) == 1 );
  assert ( isValidCard(SPADES('6') ) == 1 );
  assert ( isValidCard(SPADES('7') ) == 1 );
  assert ( isValidCard(SPADES('8') ) == 1 );
  assert ( isValidCard(SPADES('9') ) == 1 );
  assert ( isValidCard(SPADES('X') ) == 1 );
  assert ( isValidCard(SPADES('J') ) == 1 );
  assert ( isValidCard(SPADES('Q') ) == 1 );
  assert ( isValidCard(SPADES('K') ) == 1 );
  assert ( isValidCard(SPADES('A') ) == 1 );
  assert ( isValidCard(SPADES('B') ) == 0 );
  assert ( isValidCard(SPADES('C') ) == 0 );
  assert ( isValidCard(SPADES('D') ) == 0 );
  assert ( isValidCard(HEARTS('2') ) == 1 );
  assert ( isValidCard(CLUBS('2') ) == 1 );
  assert ( isValidCard(DIAMONDS('2') ) == 1 );
  assert ( isValidCard(420) == 0 );
  assert ( isValidCard(-1) == 0 );
  assert ( isValidCard(512) == 0 );
  assert ( isValidCard(-512) == 0 );
  assert ( isValidCard(69420) == 0 );
  

  // duplicated DIAMONDS('A') on hand A
  int x15[] = { DIAMONDS('A'), HEARTS('2'), SPADES('4'), DIAMONDS('A'), CLUBS('4') };
  int y15[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x15, y15 ) == RES_INVALID );

  // duplicated DIAMONDS('4') on hand B
  int x16[] = { DIAMONDS('A'), HEARTS('2'), SPADES('4'), DIAMONDS('X'), CLUBS('4') };
  int y16[] = { DIAMONDS('4'), DIAMONDS('4'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x16, y16 ) == RES_INVALID );

  // Duplicated DIAMONDS('6') in between players, last of 5 at hands
  int x20[] = { DIAMONDS('2'), DIAMONDS('3'), DIAMONDS('4'), DIAMONDS('5'), DIAMONDS('6') };
  int y20[] = { DIAMONDS('7'), DIAMONDS('8'), DIAMONDS('9'), DIAMONDS('X'), DIAMONDS('6') };
  assert ( checkForDuplicates ( x20, y20 ) == 1 );

  // Duplicated DIAMONDS('2') at  player A
  int x21[] = { DIAMONDS('2'), DIAMONDS('3'), DIAMONDS('4'), DIAMONDS('5'), DIAMONDS('2') };
  int y21[] = { DIAMONDS('7'), DIAMONDS('8'), DIAMONDS('9'), DIAMONDS('X'), DIAMONDS('J') };
  assert ( checkForDuplicates ( x21, y21 ) == 1 );

  // Duplicated DIAMONDS('X') at  player B
  int x22[] = { DIAMONDS('2'), DIAMONDS('3'), DIAMONDS('4'), DIAMONDS('5'), DIAMONDS('6') };
  int y22[] = { DIAMONDS('7'), DIAMONDS('8'), DIAMONDS('9'), DIAMONDS('X'), DIAMONDS('X') };
  assert ( checkForDuplicates ( x22, y22 ) == 1 );

  int straightFlush1[] = { CLUBS('J'), CLUBS('X'), CLUBS('9'), CLUBS('8'), CLUBS('7')};
  int straightFlush2[] = { HEARTS('A'), HEARTS('J'), HEARTS('Q'), HEARTS('K'), HEARTS('X')};
  int straightFlush3[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int straightFlush4[] = { DIAMONDS('A'), DIAMONDS('J'), DIAMONDS('Q'), DIAMONDS('K'), DIAMONDS('X')};
  int fourOfKind1[] = { CLUBS('X'), HEARTS('X'), DIAMONDS('X'), SPADES('X'), CLUBS('4')};
  int fourOfKind2[] = { CLUBS('X'), HEARTS('X'), DIAMONDS('X'), SPADES('4'), CLUBS('4')};
  int fourOfKind3[] = { CLUBS('2'), HEARTS('2'), DIAMONDS('2'), SPADES('2'), CLUBS('3')};
  int fourOfKind4[] = { HEARTS('8'), HEARTS('7'), SPADES('8'), DIAMONDS('8'), CLUBS('8')};

  assert ( isStraightFlush(straightFlush1) == 1 );
  assert ( isStraightFlush(straightFlush2) == 1 );
  assert ( isStraightFlush(straightFlush3) == 0 );
  assert ( isStraightFlush(straightFlush4) == 1 ); 
  assert ( isFourOfKind(fourOfKind1) == 1 );
  assert ( isFourOfKind(fourOfKind2) == 0 );
  assert ( isFourOfKind(fourOfKind3) == 1 );
  assert ( isFourOfKind(fourOfKind4) == 1 );

  assert ( comparePokerHands(straightFlush1, straightFlush2) == RES_WIN_B );
  assert ( comparePokerHands(straightFlush2, straightFlush4) == RES_DRAW );
  assert ( comparePokerHands(straightFlush4, straightFlush1) == RES_WIN_A );
  assert ( comparePokerHands(fourOfKind1, fourOfKind3) == RES_WIN_A );
  assert ( comparePokerHands(fourOfKind4, fourOfKind1) == RES_WIN_B );
  assert ( comparePokerHands(fourOfKind1, fourOfKind2) == RES_INVALID );
  assert ( comparePokerHands(fourOfKind3, fourOfKind4) == RES_WIN_B );
  assert ( comparePokerHands(straightFlush1, fourOfKind3) == RES_WIN_A );
  assert ( comparePokerHands(fourOfKind4, straightFlush4) == RES_WIN_B );

  int fullHouse1[] = {CLUBS('A'), HEARTS('A'), DIAMONDS('A'), CLUBS('K'), DIAMONDS('K')};
  int fullHouse2[] = {CLUBS('Q'), HEARTS('Q'), DIAMONDS('Q'), HEARTS('K'), SPADES('K')};
  int flush1[] = {CLUBS('8'), CLUBS('J'), CLUBS('4'), CLUBS('5'), CLUBS('2')};
  int flush2[] = {HEARTS('8'), HEARTS('Q'), HEARTS('4'), HEARTS('5'), HEARTS('2')};
  int flush3[] = {SPADES('A'), SPADES('Q'), SPADES('4'), SPADES('5'), SPADES('2')};
  int flush4[] = {DIAMONDS('A'), DIAMONDS('Q'), DIAMONDS('4'), DIAMONDS('5'), DIAMONDS('3')};
  int flush5[] = {HEARTS('A'), HEARTS('Q'), HEARTS('4'), HEARTS('5'), HEARTS('3')};

  assert ( isFullHouse(fullHouse1) == 1 );
  assert ( isFullHouse(fullHouse2) == 1 );
  assert ( isFlush(flush1) == 1 );
  assert ( isFlush(flush2) == 1 );
  assert ( isFlush(flush3) == 1 );
  assert ( isFlush(fourOfKind1) == 0 );
  assert ( isFlush(fourOfKind2) == 0 );
  assert ( isFlush(fullHouse1) == 0 );

  assert ( comparePokerHands(fullHouse1, fullHouse2) == RES_WIN_A );
  assert ( comparePokerHands(flush1, fullHouse2) == RES_WIN_B );
  assert ( comparePokerHands(flush2, flush3) == RES_WIN_B );
  assert ( comparePokerHands(flush3, flush4) == RES_WIN_B );
  assert ( comparePokerHands(flush4, flush5) == RES_DRAW );

  int straight1[] = {CLUBS('8'), SPADES('X'), CLUBS('9'), SPADES('J'), CLUBS('7')};
  int straight2[] = {SPADES('8'), CLUBS('X'), SPADES('9'), CLUBS('Q'), SPADES('7')};
  int straight3[] = {HEARTS('8'), HEARTS('X'), DIAMONDS('9'), HEARTS('Q'), DIAMONDS('J')};
  
  assert ( isStraight(straight1) == 1 );
  assert ( isStraight(straight2) == 0 );
  assert ( isStraight(straight3) == 1 );

  assert ( comparePokerHands(straight1, straight3) == RES_WIN_B );

  int threeOfKind1[] = {CLUBS('8'), SPADES('8'), HEARTS('8'), SPADES('J'), CLUBS('7')};
  int threeOfKind2[] = {CLUBS('8'), SPADES('8'), HEARTS('Q'), SPADES('J'), CLUBS('7')};
  int threeOfKind3[] = {CLUBS('9'), SPADES('9'), HEARTS('9'), SPADES('A'), CLUBS('K')};
  
  assert ( isThreeOfKind(threeOfKind1) == 1 );
  assert ( isThreeOfKind(threeOfKind2) == 0 );
  assert ( isThreeOfKind(threeOfKind3) == 1 );

  assert ( comparePokerHands(threeOfKind1, threeOfKind3) == RES_WIN_B );

  int twoPair1[] = {CLUBS('8'), SPADES('8'), HEARTS('J'), SPADES('J'), CLUBS('3')};
  int twoPair2[] = {CLUBS('8'), SPADES('9'), HEARTS('Q'), SPADES('J'), CLUBS('7')};
  int twoPair3[] = {CLUBS('9'), SPADES('9'), HEARTS('X'), SPADES('X'), CLUBS('K')};
  int twoPair4[] = {HEARTS('9'), DIAMONDS('9'), CLUBS('X'), DIAMONDS('X'), SPADES('K')};
  int twoPair5[] = {HEARTS('9'), DIAMONDS('9'), CLUBS('X'), DIAMONDS('X'), CLUBS('Q')};
  
  assert ( isTwoPair(twoPair1) == 1 );
  assert ( isTwoPair(twoPair2) == 0 );
  assert ( isTwoPair(twoPair3) == 1 );
  assert ( isTwoPair(twoPair4) == 1 );
  assert ( isTwoPair(twoPair5) == 1 );

  assert ( comparePokerHands(twoPair1, twoPair3) == RES_WIN_A );
  assert ( comparePokerHands(twoPair3, twoPair4) == RES_DRAW );
  assert ( comparePokerHands(twoPair3, twoPair5) == RES_WIN_A );

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
}
#endif /* __PROGTEST__ */

