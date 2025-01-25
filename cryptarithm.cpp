#include "stdlib.h"
#include "vector"
#include "cstdio"
#include "stdint.h"
#include "cryptarithm.h"
#include <cstdarg>

void cryptarithm::string_to_int_by_permutation(char* str, char* perm, int* val) {
    // This function takes in a word, e.g. "more", which has been converted to "4561"
    // And a permutation, e.g., "8675309214", which means that '0' becomes 8, '1' becomes 6, etc.
    // so '4561' becomes 3096
    // And produces the relevant value and places it in val
    return;
}

void cryptarithm::get_permutation_update(char* prev, char* curr, uint8_t* firsts, uint8_t* diff) {
    // This function takes in permutation prev, e.g., 8675309214,
    // and finds the next permutation that does *not* put zero in a position
    // where 'firsts' is true (e.g., if the 'firsts' array starts with a 1, zero
    // cannot be at the beginning of the string) and where at least one change has
    // been made to the digits that matter (those before a '2' in the 'firsts' array)

    // The next permutation goes into 'curr';
    // The differences between each value go into 'diff'

    // Example:
    // prev:   8675309124
    // firsts: 1000100222
    // go through permutations 8675309124, 8675309142, 8675309214, 8675309241,
    // 8675309412, 8675309421, to 8675310249
    // curr:   8675310249

    // prev:  8  6  7  5  3  0  9  1  2  4
    // curr:  8  6  7  5  3  1  0  2  4  9
    // diff:  0  0  0  0  0  1 -9  1  2  5
    return;
}

void cryptarithm::string_to_int_by_diff(char* str, int* val, uint8_t* diff) {
    // This function takes a string that has been converted by an old permutation
    // to be the value in val, and updates the value based on the diff
    return;
}

char * cryptarithm::int_to_string_by_permutation(char* str, char* letters, char* perm, int* val) {
    // This function does a double substitution
    // Example:
    // val:          12271
    // converts it by permutation in reverse:
    // perm:    8675309124
    // result:       78827
    // then, based on letters:
    // letters: sendmor
    // final result: 788n7
}

int cryptarithm::operation(cryptarithm::Operat op_code, int* vals) {
    // If op_code is Addition, returns the sum of all the ints in the null-terminated array vals
    // If subtraction, takes the first and subtracts the rest from it
    // If multiplication, returns the product
    // If division, can only be two; return floor division result
}

char * * find_cryptarithms(cryptarithm::Operat operation, int operands...) {
    // Get a vector of the input words
    std::vector<char *> words;
    std::va_list args;
    va_start(args, operands);
    while (operands--) words.push_back(va_arg(args, char *));
    va_end(args);
    
    // Collect all the distinct letters
    char letters[11] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    uint8_t firsts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char * filler = letters;
    for (char * letter : words) {
        while(*letter) {
            filler = letters;
            while(*filler && *filler != *letter) ++filler;
            if (!*filler) if (filler - letter < 10) *filler = *letter; else return NULL;
            ++letter;
        }
    }
    printf("%s\n", letters);

    return NULL;
}

int main() {
    find_cryptarithms(cryptarithm::Addition, 3, "send", "more", "money");
    return 0;
}