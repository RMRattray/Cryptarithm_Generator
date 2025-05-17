#ifndef Q_FINDER_H
#define Q_FINDER_H

#include <QObject>
#include <string>
#include <vector>
#include "../backend/backend.h"
#include "../backend/finder.h"
#include "../backend/trie.h"
#include "filereadstatus.h"

class QFinder : public QObject
{
    Q_OBJECT
    public:
        cryptarithm::Finder myFinder;
        std::vector<std::string> words;
    signals:
        void signal_trie_read(FileReadStatus status, int word_count);
        void signal_words_found();
    public slots:
        void slot_read_file(QString filename);
    private slots:
        void slot_find_cryptarithms(request_data req);
};

#endif 