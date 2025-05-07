#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "backend.h"
#include "finder.h"
#include "trie.h"

using namespace cryptarithm;

std::vector<std::string> Finder::find_cryptarithms(request_data given_req) {
    return find_cryptarithms(given_req, false);
}

template <typename T>
typename std::vector<T>::iterator truly_unique(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
    typename std::vector<T>::iterator tortoise = start;
    typename std::vector<T>::iterator hare = start;
    typename std::vector<T>::iterator achilles;
    while(hare < end) {
        achilles = hare;
        while (achilles < end && *achilles == *hare) ++achilles;
        if (achilles == std::next(hare)) {
            *tortoise = *hare;
            ++tortoise;
        }
        hare = achilles;
    }
    return tortoise;
}

std::vector<std::string> Finder::find_cryptarithms(request_data given_req, bool all_possible)
{
    req = &given_req;
    std::cout << "Starting to find cryptarithms.\n";
    gather_letters();
    std::cout << "Gathered letters:\n";
    std::cout << letters << std::endl;
    recursively_permute(0);
    std::cout << "Developed search strings\n";
    for (std::string& search_string : all_search_strings) {
        clean_string(&search_string);
    }
    std::cout << "Cleaned search strings\n";
    // If we're looking for all possible answers,
    // just remove duplicates of search strings for efficiency
    std::sort(all_search_strings.begin(), all_search_strings.end());
    std::vector<std::string>::iterator last;
    if (all_possible) last = unique(all_search_strings.begin(), all_search_strings.end());
    // Otherwise, remove any strings that are duplicated at all (unsolvable puzzles)
    else last = truly_unique<std::string>(all_search_strings.begin(), all_search_strings.end());
    std::cout << "Search string count: " << (last - all_search_strings.begin());
    std::cout << "\tRemoved " << all_search_strings.end() - last << " as duplicates.\n";
    all_search_strings.erase(last, all_search_strings.end());

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

void Finder::clean_string(std::string * s)
{
    // Example string: "4e240a" -> "0e102a"
    // 4e240a -> 0e20:a -> 0e10:a -> 0e102a
    char * l = &((*s)[0]); // Position in string
    char * m; // Position in rest of string
    char d = '0'; // Next digit to use
    char f; // Digit being replaced
    char r = '9' + 1; // Symbol used for replacing
    while (f = *l)
    {
        if (f >= d && f <= 'a') {
            // We found a digit (or a symbol)
            m = l;
            while(*m) {
                if (*m == f) *m = d;
                else if (*m == d) *m = r;
                ++m;
            }
            ++d;
            ++r;
        }
        ++l;
    }
}

void Finder::read_words(std::string s) {
    word_trie = get_trie_from_file(s);
}