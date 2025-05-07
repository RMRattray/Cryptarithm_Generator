#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

#define ALPHABET_SIZE 'z' - 'a' + 1

namespace cryptarithm {

struct TrieNode {
    bool terminal;
    struct TrieNode * next[ALPHABET_SIZE];
};

TrieNode * newTrieNode(void);

void insert_to_trie(TrieNode * root, std::string word);

void get_words(std::vector<std::string> * sols, TrieNode * root, TrieNode * current, char * word_start, char * letter, std::string used_letters, bool multiword);

void free_trie(TrieNode * root);

TrieNode * get_trie_from_file(std::string filename);

}

#endif