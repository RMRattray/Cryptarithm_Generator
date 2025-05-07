#ifndef FINDER_H
#define FINDER_H

#include <cstdint>
#include <string>
#include <vector>
#include "backend.h"
#include "trie.h"

namespace cryptarithm
{
class Finder {
    public:
        /// Public function
        std::vector<std::string> find_cryptarithms(request_data req);
        std::vector<std::string> find_cryptarithms(request_data req, bool all_possible);
        void read_words(std::string word_file_name);
        // Public member
        TrieNode * word_trie;
    private:
        //////////////////////
        // Private members
        char letters[11] = {'\0'};
        uint8_t firsts[10] = { 0 };
        int max = 0;
        char digits[10] = {'\0'};
        char rechars[10] = {'\0'};
        std::vector<char *> character_finds[10];
        request_data * req;
        std::vector<std::string> all_search_strings;
        ///////////////////////
        // Private functions
        void gather_letters(void);
        void recursively_permute(int index);
        void do_arithmetic(void);
        void clean_string(std::string * s);
};
}

#endif