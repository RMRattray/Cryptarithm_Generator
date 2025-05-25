#include <QObject>
#include <QString>
#include <iostream>
#include "qfinder.h"
#include "../backend/backend.h"
#include "../backend/finder.h"
#include "../backend/trie.h"

void QFinder::slot_read_file(QString filename) {
    #ifdef DEBUG
    std::cout << "The slot to read in a file is running, filename: " << filename.toStdString() << std::endl;
    #endif
    int c = myFinder.read_words(filename.toStdString());
    emit signal_trie_read(myFinder.word_trie_complete ? FileReadStatus::FINISHED : FileReadStatus::FAILED, c);
    #ifdef DEBUG
    std::cout << "The slot to read in a file is done running.\n";
    #endif
    return;
}

void QFinder::slot_find_cryptarithms(request_data req) {
    #ifdef DEBUG
    std::cout << "The slot to find cryptarithms is running.  Requested words:\n";
    for (std::string word : req.factors) std::cout << "\t" << word << std::endl;
    #endif
    words = myFinder.find_cryptarithms(req);
    #ifdef DEBUG
    std::cout << "Should have found all the answers now.  Those words are:\n";
    for (std::string word : words) std::cout << "\t" << word << std::endl;
    #endif
    emit signal_words_found();
    return;
}