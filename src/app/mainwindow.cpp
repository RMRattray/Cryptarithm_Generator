#include "mainwindow.h"
#include "backend.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <iostream>
#include <QCloseEvent>
#include <QMessageBox>

Window::Window(QWidget *parent) :
 QWidget(parent)
 {
    // Set size of the window
    // setFixedSize(100, 90);

    // General look of the main window:
    /////////////////////////////////////////////////////
    // Cryparithm Generator                     _ [] X //
    /////////////////////////////////////////////////////
    //                        //                       //
    // Operation: [____Add_V] //  Solutions:           //
    //                        //                       //
    //          [___________] //                       //
    //      [+] [___________] //                       //
    //          ------------- //                       //
    //          [___________] //                       //
    //                        //                       //
    // [Reset] [   GO    ]    //                       //
    /////////////////////////////////////////////////////

    // Make a main layout object
    main_split_layout = new QHBoxLayout;

    // Split into two areas
    left_stack_layout = new QVBoxLayout;
    QVBoxLayout * right_stack_layout = new QVBoxLayout;
    main_split_layout->addItem(left_stack_layout);
    main_split_layout->addItem(right_stack_layout);
    main_split_layout->setStretchFactor(left_stack_layout, 0);
    main_split_layout->setStretchFactor(right_stack_layout, 1);

    // First thing in the left-side stack
    // are the dropdowns for operation
    // and word count
    operation_combo_box = new QComboBox();
    operation_combo_box->addItem("addition");
    operation_combo_box->addItem("subtraction");
    operation_combo_box->addItem("multiplication");
    word_count_combo_box = new QComboBox();
    word_count_combo_box->addItem("single");
    word_count_combo_box->addItem("multiple");
    unique_sol_combo_box = new QComboBox();
    unique_sol_combo_box->addItem("with unique solutions");
    unique_sol_combo_box->addItem("with any solutions");

    QFormLayout * selections = new QFormLayout();
    selections->addRow(new QLabel(tr("Operation")), operation_combo_box);
    selections->addRow(new QLabel(tr("Word count ")), word_count_combo_box);
    selections->addRow(new QLabel(tr("Solutions")), unique_sol_combo_box);

    left_stack_layout->addItem(selections);
    
    // Next thing is the arithmetic text area
    arithmetic_args_box = new ArithBox();
    left_stack_layout->addWidget(arithmetic_args_box);
    
    // Last thing are the buttons to go
    // and to reset

    QHBoxLayout * button_area = new QHBoxLayout();
    go_button = new QPushButton("GO");
    reset_button = new QPushButton("Reset");
    button_area->addWidget(reset_button, 1);
    button_area->addWidget(go_button, 2);
    button_area->addStretch(1);

    left_stack_layout->addItem(button_area);

    // And on the right side, the file selector:
    file_select_box = new FileSelectBox;
    solution_scroll_area = new QScrollArea;
    solution_scroll_area->setWidgetResizable(true);
    right_stack_layout->addWidget(file_select_box);
    right_stack_layout->addWidget(solution_scroll_area);
    
    // And for the scroll area, a VBoxLayout in a ScrollWidget
    QWidget * right_scroll_widget = new QWidget();
    solution_scroll_area->setWidget(right_scroll_widget);
    right_word_list_stack_layout = new QVBoxLayout;
    right_scroll_widget->setLayout(right_word_list_stack_layout);

    this->setLayout(main_split_layout);

    // And let's not forget the finder object itself!
    my_q_finder = new QFinder();
    // my_q_finder->slot_read_file("words.txt");

    // And the signals and slots!
    /////////////////////////////////

    // Make the buttons to modify the arithmetic box from outside functional
    connect(reset_button, SIGNAL(clicked()), arithmetic_args_box, SLOT(reset_factor_stack()));
    connect(operation_combo_box, SIGNAL(currentIndexChanged(int)), arithmetic_args_box, SLOT(change_focus_op(int)));
    
    // Signals and slots to calculate the solution
    connect(go_button, SIGNAL(clicked()), this, SLOT(slot_calculate_request()));
    connect(this, SIGNAL(request_data_ready(request_data)), my_q_finder, SLOT(slot_find_cryptarithms(request_data)));
    connect(my_q_finder, SIGNAL(signal_words_found()), this, SLOT(slot_populate_solution_area()));

    // Signals and slots to read in the word list
    connect(file_select_box, SIGNAL(signal_read_word_list(QString)), my_q_finder, SLOT(slot_read_file(QString)));
    connect(my_q_finder, SIGNAL(signal_trie_read(FileReadStatus, int)), file_select_box, SLOT(slot_light_indicator(FileReadStatus, int)));
}

void Window::slot_calculate_request() {
    if (my_q_finder->myFinder.word_trie) {
        request_data req = arithmetic_args_box->yield_text_contents();
        req.all_possible = (unique_sol_combo_box->currentIndex() != 0);
        emit request_data_ready(req);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Select a word list file before attempting to find words.");
        msgBox.exec();
    }
}

void Window::slot_populate_solution_area() {
    // Remove old listings
    while (QLayoutItem *item = right_word_list_stack_layout->takeAt(0)) {
        QWidget *widget = item->widget();
        if (widget) widget->deleteLater();
        delete item; // Delete the layout item
    }
    for (std::string word : my_q_finder->words) {
        QLabel * newlabel = new QLabel(QString::fromStdString(word));
        right_word_list_stack_layout->addWidget(newlabel);
    }
}

void Window::closeEvent(QCloseEvent * event) {
    std::cout << "The special close event runs\n";
    if (my_q_finder->myFinder.word_trie) cryptarithm::free_trie(my_q_finder->myFinder.word_trie);
    event->accept();
}