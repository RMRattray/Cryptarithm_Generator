#include <QObject>
#include <QString>
#include <iostream>
#include "qfinder.h"
#include "../backend/backend.h"
#include "../backend/finder.h"
#include "../backend/trie.h"

void QFinder::slot_read_file(QString filename) {
    std::cout << "The slot to read in a file is running, filename: " << filename.toStdString() << std::endl;
    myFinder.read_words(filename.toStdString());
    emit signal_trie_read(myFinder.word_trie_complete ? FileReadStatus::FINISHED : FileReadStatus::FAILED, 0);
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