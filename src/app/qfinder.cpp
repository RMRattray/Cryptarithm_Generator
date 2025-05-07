#include <QObject>
#include <string>
#include <iostream>
#include "qfinder.h"
#include "../backend/backend.h"
#include "../backend/finder.h"
#include "../backend/trie.h"

void QFinder::slot_read_file(std::string filename) {
    emit signal_trie_read(false);
    myFinder.read_words(filename);
    emit signal_trie_read(myFinder.word_trie_complete);
    return;
}

void QFinder::slot_find_cryptarithms(request_data req) {
    std::cout << "The slot to find cryptarithms is running.  Requested words:\n";
    for (std::string word : req.factors) std::cout << "\t" << word << std::endl;
    words = myFinder.find_cryptarithms(req);
    std::cout << "Should have found all the answers now.  Those words are:\n";
    for (std::string word : words) std::cout << "\t" << word << std::endl;
    emit signal_words_found();
    return;
}