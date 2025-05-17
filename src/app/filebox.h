#ifndef FILE_BOX_H
#define FILE_BOX_H

#include <QFrame>
#include <QPushButton>
#include <string>
#include "../backend/trie.h"
#include "filereadstatus.h"
#include <QRect>
#include <QString>

class QLineEdit;
class QLabel;
class QPalette;

class StatusLight : public QPushButton {
    public:
        explicit StatusLight(QWidget *parent = NULL);
        void setColor(QColor color);
    private:
        QPalette pal;
};

class FileSelectBox : public QFrame {
    Q_OBJECT
    public:
        explicit FileSelectBox(QWidget *parent = NULL);
        bool word_list_ready;
        int word_list_count;
    signals:
        void signal_read_word_list(QString filename);
    public slots:
        void slot_light_indicator(FileReadStatus status, int word_count);
    private slots:
        void get_file(void);
    private:
        QLineEdit* file_location;
        StatusLight* status_light;
        QLabel* status_label;
        QPushButton* get_file_button;
};

#endif