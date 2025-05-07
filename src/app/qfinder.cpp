#include <QObject>
#include <string>
#include "qfinder.h"
#include "../backend/backend.h"
#include "../backend/finder.h"
#include "../backend/trie.h"

void QFinder::slot_read_file(std::string filename) {
    emit signal_trie_read(false);
    if (myFinder.word_trie) cryptarithm::free_trie(myFinder.word_trie);
    myFinder.word_trie = cryptarithm::get_trie_from_file(filename);
    emit signal_trie_read(true);
    return;
}

void QFinder::slot_find_cryptarithms(request_data req) {
    words = myFinder.find_cryptarithms(req);
    emit signal_words_found();
    return;
}