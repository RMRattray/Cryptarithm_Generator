#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "wordboxbox.h"

FactorBox::FactorBox(QWidget *parent) : QFrame(parent) {
    // Main layout is two items
    QHBoxLayout * main_layout = new QHBoxLayout;
    main_layout->addSpacing(30);
    factor_box = new QLineEdit;
    main_layout->addWidget(factor_box);
    setLayout(main_layout);
}

std::string FactorBox::yield_text_contents() {
    return factor_box->text().toStdString();
}

void FactorBox::blank_contents() {
    factor_box->setText(tr(""));
}

ArithBox::ArithBox(QWidget *parent) : QFrame(parent) {
    // Main layout is a vertical stack
    QVBoxLayout * main_layout = new QVBoxLayout;
    main_layout->addStretch(1);

    // First object in it is the factor stack
    factor_stack = new QVBoxLayout;
    factor_stack->addWidget(new FactorBox);
    main_layout->addLayout(factor_stack);

    // Button to add more factors, next to last factor
    operation_button = new QPushButton("+");
    operation_button->setFixedWidth(30);

    // Last factor in box
    final_factor_box = new QLineEdit;
    QHBoxLayout * op_button_and_final_factor_box = new QHBoxLayout;
    op_button_and_final_factor_box->addWidget(operation_button);
    op_button_and_final_factor_box->addWidget(final_factor_box);
    main_layout->addLayout(op_button_and_final_factor_box);

    // Line before product
    QFrame * horizontal_line = new QFrame;
    horizontal_line->setFrameShape(QFrame::HLine);
    main_layout->addWidget(horizontal_line);

    // And product
    product_box = new QLineEdit;
    main_layout->addWidget(product_box);

    factors = 2;

    // Connect the button's clicked signal to the slot to add a text box
    connect(operation_button, SIGNAL(clicked()), this, SLOT(add_text_box()));

    setLayout(main_layout);
}

void ArithBox::add_text_box() {
    factor_stack->addWidget(new FactorBox);
    ++factors;
}

void ArithBox::reset_factor_stack() {
    QLayoutItem *child;
    while ((child = factor_stack->takeAt(1)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

void ArithBox::change_focus_op(Operation op) {
    switch (op)
    {
    case ADDITION:
        operation_button->setText(tr("+"));
        break;
    case SUBTRACTION:
        operation_button->setText(tr("-"));
        break;
    case MULTIPLICATION:
        operation_button->setText(tr("x"));
    default:
        break;
    }
}
// private slots:
//     void addTextBox() {
//         // Create a new text box and add it to the layout
//         QLineEdit *newTextBox = new QLineEdit(this);
//         layout()->addWidget(newTextBox);
//     }
// };