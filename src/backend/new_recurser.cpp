#include "backend.h"
#include <string.h>
#include <cstdint>
#include "vector"

// An array of all letters that appear in the current words, e.g., "sendmory"
char glbl_letters[11] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
// An array indicating which letters are the first in a word and thus cannot be zero.
uint8_t firsts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// The length of the glbl_letters array
int max = 0;
// An array of the digits to which they are being substituted in the current permutation
char digits[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
// Locations of each character in the original words
std::vector<char *> character_finds[10];
// Globalized version of req;
request_data * glbl_req;
// A vector of the characters corresponding to each digit 0-9
char rechars[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
// A vector of all possible resulting strings
std::vector<std::string> all_possible_strings;

// std::string abcdize_word(std::string word) {
//     std::string abcdized = "";
//     char* code_letter;
//     for (char l : word) {
//         code_letter = glbl_letters;
//         while (*code_letter != l) ++code_letter;
//         abcdized.push_back('a' + code_letter - glbl_letters);
//     }
// }

void recursively_permute(int index) {
    // For a point in the permutation, consider all possible digits not already assigned to a letter
    char v = '0' + firsts[index];

    // For the first, replace that one letter

    for ( ; v <= '9'; ++v) {
        if (strchr(digits, v)) continue;
        digits[index] = v;
        
        // For each of such, update letters in words
        for (char * loc : character_finds[index]) *loc = v;
        // And in the decode string
        rechars[v - '0'] = glbl_letters[index];

        if (index == max) do_arithmetic();
        else recursively_permute(index + 1);

        // Clean decode string
        rechars[v - '0'] = '\0';
    }
    digits[index] = '\0';
}

void do_arithmetic() {
    // First, combine factors to get product of desired type
    long long int product = (glbl_req->op == Operation::MULTIPLICATION);
    long long int f;
    for (std::string factor : glbl_req->factors) {
        f = atol(&factor[0]);
        switch (glbl_req->op)
        {
        case Operation::ADDITION:
            product += f;
            break;
        case Operation::SUBTRACTION:
            product -= f;
        default:
            product *= f;
            break;
        }
    }
    // Then, convert product to string
    char product_str[20];
    sprintf(product_str, "%lld", product);

    char * letter = product_str;
    while (*letter) {
        char replace = rechars[*letter - '0'];
        if (replace) *letter = replace;
        ++letter;
    }

    // Deep copy string and insert to vector
    all_possible_strings.push_back(std::string(product_str));
    return;
}

std::vector<std::string> find_cryptarithms(request_data req) {
    
    // Collect all the distinct letters and mark which are first
    char * filler = glbl_letters;
    // Using the & here causes it to access the same string, not a copy
    for (std::string& factor : req.factors) {
        char * letter = &(factor[0]);
        while(*letter) {
            filler = glbl_letters;
            while(*filler && *filler != *letter) ++filler;
            if (!*filler) if (filler - glbl_letters < 10) {
                *filler = *letter;
            }
            if (letter == factor) firsts[filler - glbl_letters] = 1;
            character_finds[filler - glbl_letters].push_back(letter);
            ++letter;
        }
    }
    max = strlen(glbl_letters) - 1;

    glbl_req = &req;
    recursively_permute(0);
    // Recursively go through them

    return all_possible_strings;
}