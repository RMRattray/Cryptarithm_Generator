#include <QFrame>
#include <QPalette>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QColor>
#include <QHBoxLayout>
#include <string>
#include "filebox.h"
#include "filereadstatus.h"
#include <QFileDialog>
#include <QString>
#include <iostream>

StatusLight::StatusLight(QWidget *parent) : QPushButton(parent) {
    // this->setAutoFillBackground(true);
    pal = QPalette();
    this->setFixedWidth(20);
    this->setFixedHeight(20);
}

void StatusLight::setColor(QColor color) {
    // this->setAutoFillBackground(true);
    pal.setColor(QPalette::Button, color);
    this->setPalette(pal);
    this->repaint();
}

FileSelectBox::FileSelectBox(QWidget *parent) : QFrame(parent) {
    QVBoxLayout * main_layout = new QVBoxLayout;
    file_location = new QLineEdit;
    file_location->setEnabled(false);
    QHBoxLayout * lower_row = new QHBoxLayout;
    status_light = new StatusLight;
    status_light->setColor(Qt::red);
    status_label = new QLabel;
    status_label->setText(tr("No word list"));
    get_file_button = new QPushButton("Select file");
    lower_row->addWidget(status_light);
    lower_row->addSpacing(10);
    lower_row->addWidget(status_label);
    lower_row->addStretch(1);
    lower_row->addWidget(get_file_button);
    main_layout->addWidget(file_location);
    main_layout->addItem(lower_row);

    this->setLayout(main_layout);

    word_list_ready = false;
    word_list_count = 0;

    connect(get_file_button, SIGNAL(clicked()), this, SLOT(get_file()));
}

void FileSelectBox::slot_light_indicator(FileReadStatus status, int word_count) {
    switch (status)
    {
    case FileReadStatus::NONE:
        status_light->setColor(Qt::red);
        status_label->setText(tr("No word list"));
        word_list_ready = false;
        word_list_count = 0;
        get_file_button->setEnabled(true);
        break;
    case FileReadStatus::FAILED:
        status_light->setColor(Qt::red);
        status_label->setText(tr("Failed to read file"));
        word_list_ready = false;
        word_list_count = 0;
        get_file_button->setEnabled(true);
        break;
    case FileReadStatus::READING:
        status_light->setColor(Qt::yellow);
        status_label->setText(tr("Reading word list"));
        word_list_ready = false;
        word_list_count = 0;
        get_file_button->setEnabled(false);
        break;
    case FileReadStatus::FINISHED:
        status_light->setColor(Qt::green);
        status_label->setText(QString("%1 words read").arg(word_count));
        word_list_ready = true;
        word_list_count = word_count;
        get_file_button->setEnabled(true);
        break;
    default:
        break;
    }
}

void FileSelectBox::get_file(void) {
    QString file_name = QFileDialog::getOpenFileName(this, tr("Select word list file"), QDir::currentPath(), tr("Text files (*.txt)"));
    file_location->setText(file_name);
    if (file_name != tr("")) {    
        slot_light_indicator(FileReadStatus::READING, 0);
        emit signal_read_word_list(file_name);
    }
}