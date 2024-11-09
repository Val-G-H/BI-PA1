# Introduction

Assignment:
 - Evaluate two poker hands and decide who would win


Refer to the assignment details [here](Assignment.txt) and to poker rules [here](https://en.wikipedia.org/wiki/List_of_poker_hands)

# Current solution
1. Verify if the cards given are valid
    - if not RES_INVALID
2. Verify if there are no duplicates across both decks
    - if not RES_INVALID
3. Evaluate both hands for having a **straight flush**
    - note the high ace ruleset, `(A 2 3 4 5)` is not considered
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - if both have it, highest *card value* wins
4. Evaluate both hands for having a **four-of-kind**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - if both have it, highest four-of-kind *card value* wins
    - cannot draw due to duplication restriction
5. Evaluate both hands for having a **full house**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - if both have it, highest three-of-kind *card value* wins
    - cannot draw due to duplication restriction
6. Evaluate both hands for having a **flush**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - cannot draw due to duplication restriction
7. Evaluate both hands for havin a **straight**
    - note the high ace ruleset, `(A 2 3 4 5)` is not considered
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - can draw
7. Evaluate both hands for having a **three-of-kind**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - cannot draw due to duplication restriction
8. Evaluate both hands for having a **two pair**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - can draw
9. Evaluate both hands for having a **one pair**
    - the one who has it wins (RES_WIN_A || RES_WIN_B)
    - can draw
10. No combinations exist, the winner is now decided based on *card value*
    - can draw

Refer to implementation [here](test.c)

# To do
* (!) find and fix failing edgecases
* code cleanup
* remove redundant draw returns


# Tests

Local tests via terminal script

`for file in CZE/*_in.txt; do echo "$file"; ./a.out < "$file" | diff - "${file/in/out}"; done`