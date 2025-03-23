#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>

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
 solution_scroll_area = new QScrollArea;
 left_stack_layout = new QVBoxLayout;
 main_split_layout->addItem(left_stack_layout);
 main_split_layout->addWidget(solution_scroll_area);

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

 QFormLayout * selections = new QFormLayout();
 selections->addRow(new QLabel(tr("Operation")), operation_combo_box);
 selections->addRow(new QLabel(tr("Word count")), word_count_combo_box);

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

 this->setLayout(main_split_layout);

 // And the signals and slots!
 connect(reset_button, SIGNAL(&QPushButton::clicked), arithmetic_args_box, SLOT(&ArithBox::reset_factor_stack));
 connect(operation_combo_box, SIGNAL(&QComboBox::currentIndexChanged(int)), arithmetic_args_box, SLOT(&ArithBox::change_focus_op(int)));
}