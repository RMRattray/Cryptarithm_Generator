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
    int temp[20] = {0,};
    int result = 0;

    for (int i = 0; i < strlen(str); i++) {

        int index = str[i] - '0';
        temp[i] = (int) (perm[index] - '0');

    }

    for (int i = 0; i < strlen(str); i++) {

        result = result*10 + temp[i];

    }

    *val = result;
    printf("%d\n", *val);

    return;
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
