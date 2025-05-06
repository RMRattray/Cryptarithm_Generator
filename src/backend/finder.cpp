#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "backend.h"
#include "finder.h"

using namespace cryptarithm;

std::vector<std::string> Finder::find_cryptarithms(request_data given_req)
{
    req = &given_req;
    std::cout << "Starting to find cryptarithms.\n";
    this->gather_letters();
    std::cout << "Gathered letters:\n";
    std::cout << letters << std::endl;
    this->recursively_permute(0);
    for (std::string search_string : all_search_strings) {
        std::cout << search_string << std::endl;
    }
    std::cout << "Have all search strings:\n";
    return all_search_strings;
}

void Finder::gather_letters()
{
    char * filler = letters;
    for (std::string& factor : req->factors) {
        std::cout << factor << std::endl;
        char * letter = &(factor[0]);
        while(*letter) {
            filler = letters;
            while(*filler && *filler != *letter) ++filler;
            if (!*filler) if (filler - letters < 10) {
                *filler = *letter;
            }
            if (letter == factor) firsts[filler - letters] = 1;
            character_finds[filler - letters].push_back(letter);
            ++letter;
        }
    }
    this->max = strlen(this->letters) - 1;
    return;
}

void Finder::recursively_permute(int index)
{
    // For a point in the permutation, consider all possible digits not already assigned to a letter
    char v = '0' + firsts[index];

    // For the first, replace that one letter

    for ( ; v <= '9'; ++v) {
        if (strchr(digits, v)) continue;
        digits[index] = v;

        std::cout << "Permuting on:  " << digits << std::endl;
        
        // For each of such, update letters in words
        for (char * loc : character_finds[index]) *loc = v;
        // And in the decode string
        rechars[v - '0'] = letters[index];

        if (index == max) do_arithmetic();
        else recursively_permute(index + 1);

        // Clean decode string
        rechars[v - '0'] = '\0';
    }
    digits[index] = '\0';
    return;
}

void Finder::do_arithmetic(void)
{
    // First, combine factors to get product of desired type
    long long int product = (req->op == Operation::MULTIPLICATION);
    long long int f;
    for (std::string factor : req->factors) {
        f = atol(&factor[0]);
        switch (req->op)
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
    all_search_strings.push_back(std::string(product_str));
    return;
}