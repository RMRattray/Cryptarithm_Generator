#include "trie.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace cryptarithm;

// Function to make null trieNode
TrieNode * cryptarithm::newTrieNode(void) {
    struct TrieNode * t = (TrieNode *)malloc(sizeof(TrieNode));
    if (!t) return NULL;
    memset(t, 0, sizeof(TrieNode));
    return t;
}

void cryptarithm::insert_to_trie(TrieNode * root, std::string word) {
    char * letter = &(word[0]);
    char l;
    TrieNode * branch = root;
    while (l = *letter) {
        if (!(branch->next[l - 'a'])) branch->next[l - 'a'] = cryptarithm::newTrieNode();
        branch = branch->next[l - 'a'];
        ++letter;
    }
    branch->terminal = true;
    return;
}

void replaceChar(char * word, char oldChar, char newChar) {
    while (*word) {
        if (*word == oldChar) *word = newChar;
        ++word;
    }
}

void cryptarithm::get_words(std::vector<std::string> * sols, TrieNode * root, TrieNode * current, char * word_start, char * letter, std::string used_letters, bool multiword) {
    // Go through the trie along the letters in the search string if possible
    while (*letter >= 'a' && *letter <= 'z' && current->next[*letter - 'a']) {
        // If we finish a word in the tree, can start over
        if (multiword && current->terminal) cryptarithm::get_words(sols, root, root, word_start, letter, used_letters, multiword);
        current = current->next[*letter - 'a'];
        ++letter;
    }
    // If encountering a number, update the string and recurse
    if ((*letter >= '0' && *letter <= '9')) {
        char n = 'a';
        TrieNode * * next = current->next;
        while (n <= 'z') {
            if (*next && (used_letters.find(n) == std::string::npos)) {
                replaceChar(letter, *letter, n);
                cryptarithm::get_words(sols, root, *next, word_start, letter + 1, used_letters + n, multiword);
            }
            ++n;
            ++next;
        }
    }
    // If we reach the end of the string and the node is terminal, we found a word
    else if (!*letter && current->terminal) sols->push_back(std::string(word_start));
    // Otherwise, we either reached the end of the string in the wrong place
    return;
}

void cryptarithm::free_trie(TrieNode * root) {
    if (root == NULL) return;
    TrieNode ** child = root->next + ALPHABET_SIZE;
    while (child > root->next) {
        --child;
        cryptarithm::free_trie(*child);
    }
    free(root);
}

bool is_alpha(char * str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') *str |= 32;
        if (!(*str >= 'a' && *str <= 'z')) break;
        ++str;
    } return !(*str);
}

TrieNode * cryptarithm::get_trie_from_file(std::string filename, int * count) {

    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "WARNING! Failed to open file:\n" << filename << std::endl;
        return NULL;
    }

    TrieNode * root = cryptarithm::newTrieNode();
    if (!root) {
        input.close();
        return NULL;
    }

    int c = 0;
    char buf[MAX_WORD_LEN];
    input.getline(buf, sizeof(buf));
    while (!input.eof() && !input.fail()) {
        if (buf[0] && is_alpha(buf)) { cryptarithm::insert_to_trie(root, std::string(buf)); c++; }
        input.getline(buf, sizeof(buf));
    }
    if (input.fail() && !input.eof()) {
        std::cout << "WARNING! Failed to read line: " << buf << "\nin file: " << filename << std::endl;
        input.close();
        free_trie(root);
        return NULL;
    }

    input.close();
    *count = c;
    return root;
}