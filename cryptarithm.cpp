#include "stdlib.h"
#include "vector"
#include "cstdio"
#include "stdint.h"
#include <cstdarg>

    char * * find_cryptarithms(Operat operation, int operands...) {
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
}

int main() {
    find_cryptarithms(crypt::Addition, 3, "send", "more", "money");
    return 0;
}