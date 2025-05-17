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

// This function is similar to std::unique, which
// moves duplicates of an element in a sorted vector to the
// end of the vector.  The difference is, it moves
// any elements that are duplicated at all, including
// the first occurence of each.
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

// This is the primary logic function.  It takes in "request_data" - a list
// of addeds/subtrahends/factors and the joining operation, e.g., "send", "more",
// and "+", and outputs a list of words that can result per sideways arithmetic.
// The parameter "all_possible", if true, causes the function to return all words
// for which a cryptarithm exists; if false, the function returns only those with
// a unique solution of numbers behind them.
std::vector<std::string> Finder::find_cryptarithms(request_data given_req)
{
    // If there are no words to search against, don't bother developing search
    // strings
    if (!word_trie_complete) return std::vector<std::string>();

    // Process the request, developing clean search strings
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

    // Remove either duplicates or duplicated elements, depending on the
    // value of (all_possible);
    std::sort(all_search_strings.begin(), all_search_strings.end());
    std::vector<std::string>::iterator last;
    if (given_req.all_possible) last = unique(all_search_strings.begin(), all_search_strings.end());
    else last = truly_unique<std::string>(all_search_strings.begin(), all_search_strings.end());
    std::cout << "Search string count: " << (last - all_search_strings.begin());
    std::cout << "\n\tRemoved " << all_search_strings.end() - last << " as duplicates.\n";
    all_search_strings.erase(last, all_search_strings.end());

    // Process against word trie
    std::vector<std::string> words;
    for (std::string& search_string : all_search_strings) {
        get_words(&words, word_trie, word_trie, &(search_string[0]), &(search_string[0]), std::string(letters), false);
    }

    return words;
}

// This function gathers all the letters that occur in factors
// into the "letters" variable.  For example, given "send" and "more",
// it should be set to "sendmor", the second 'e' being redundant.
// "max" is set to the number of letters - aka, the maximum iteration depth.
// It also reports the locations of each instance of each letter
// to the "character_finds" array of vectors of character pointers.
void Finder::gather_letters()
{
    char * filler = letters;
    for (std::string& factor : req->factors) {
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
    max = strlen(this->letters) - 1;
    return;
}

// This function assigns all possible numerical values to a letter
// based on the numbers assigned to previous letter, and calls itself
// for the next letter - or, if it is at the last letter, calls
// the arithmetic function to do the math
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

// This function goes through the list of factors, which
// by the time this function is called should be completely
// turned into numbers, and produces a numerical product,
// then replaces the digits that correspond to letters in its
// case with those letters, and adds that string to the list
// of search strings
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

// This converts a search string with a mix of digits
// and letters to one with digits in a consistent order,
// revealing equivalent search strings
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

// This function reads in the word trie from
// a given file.  Should be run before attempting
// to find cryptarithms
void Finder::read_words(std::string s) {
    TrieNode * old_trie = word_trie;
    if(word_trie = get_trie_from_file(s)) word_trie_complete = true;
    else(word_trie = old_trie);
    if(old_trie && old_trie != word_trie) free_trie(old_trie);
}