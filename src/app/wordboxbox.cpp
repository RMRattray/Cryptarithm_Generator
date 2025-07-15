#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
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
    FactorBox * first_factor_box = new FactorBox;
    factor_box_ptrs.push_back(first_factor_box);
    factor_stack->addWidget(first_factor_box);
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
    FactorBox * n = new FactorBox;
    factor_stack->addWidget(n);
    factor_box_ptrs.push_back(n);
    ++factors;
}

void ArithBox::reset_factor_stack() {
    QLayoutItem *child;
    while ((child = factor_stack->takeAt(1)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
    factor_box_ptrs.erase(factor_box_ptrs.begin() + 1, factor_box_ptrs.end());
}

void ArithBox::change_focus_op(int new_index) {
    switch (new_index)
    {
    case 0:
        operation_button->setText(tr("+"));
        break;
    case 1:
        operation_button->setText(tr("-"));
        break;
    case 2:
        operation_button->setText(tr("x"));
    default:
        break;
    }
}

// mini function w/lambda in it
bool is_alpha(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isalpha(c);
    });
}

struct request_data ArithBox::yield_text_contents() {
    request_data nullo;
    request_data req;
    
    // Read in first and last factors as strings
    std::string s;
    std::string f;
    s = product_box->text().toStdString();
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    if (!is_alpha(s)) return nullo;
    bool last_not_blank = (s != std::string(""));
    f = factor_box_ptrs[0]->yield_text_contents();
    std::transform(f.begin(), f.end(), f.begin(), [](unsigned char c) { return std::tolower(c); });
    if (!is_alpha(f)) return nullo;
    bool first_not_blank = (f != std::string(""));

    // If both first word and last word are blank, invalid puzzle
    if (!first_not_blank && !last_not_blank) return nullo;
    // If one or the other is blank, we've found the blank, invalidate
    // if we find another
    bool found_one_blank = !(first_not_blank && last_not_blank);

    char decision = operation_button->text().front().toLatin1() + last_not_blank;
    switch (decision) {
        // If there is a last word and we are adding, it is effectively
        // a subtraction problem wherein the first word is the 'sum'
        case '+' + true:
            req.factors.push_back(s);
        case '-':
            if (first_not_blank) req.factors.push_back(f);
            req.op = Operation::SUBTRACTION;
            break;
        // If we are multiplying, the last word must be empty, as division
        // is not an option with integers
        case 'x':
            req.factors.push_back(f);
            req.op = Operation::MULTIPLICATION;
            break;
        case 'x' + true:
            return nullo;
        // If subtracting but the last word is not blank, operation depends
        // on whether the first word is the blank one.  If the first word
        // is blank, then we are adding
        case '-' + true:
            if (first_not_blank) {
                req.op = Operation::SUBTRACTION;
                req.factors.push_back(f);
            } else req.op = Operation::ADDITION;
            req.factors.push_back(s);
        // Normal addition case is normal addition case
        case '+':
            req.factors.push_back(f);
        default:
            req.op = Operation::ADDITION;
    }

    // Get the rest of the factors - hopefully we don't have multiple blanks
    std::vector<FactorBox *>::iterator fb = factor_box_ptrs.begin() + 1;
    while (fb < factor_box_ptrs.end()) {
        s = (*fb)->yield_text_contents();
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
        if (!is_alpha(s)) return nullo;
        if (s != std::string("")) req.factors.push_back(s);
        else if (found_one_blank) return nullo;
        else found_one_blank = true;
        ++fb;
    }
    f = final_factor_box->text().toStdString();
    std::transform(f.begin(), f.end(), f.begin(), [](unsigned char c) { return std::tolower(c); });
    if (!is_alpha(f)) return nullo;
    if (f != std::string("")) req.factors.push_back(f);
    else if (found_one_blank) return nullo;

    return req;
}