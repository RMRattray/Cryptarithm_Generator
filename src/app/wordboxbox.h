#ifndef WORD_BOX_BOX_H
#define WORD_BOX_BOX_H 

#include <QFrame>
#include <string>
#include <backend.h>

class QPushButton;
class QLineEdit;
class QVBoxLayout;

class ArithBox : public QFrame {
    Q_OBJECT
    public:
        explicit ArithBox(QWidget *parent = 0);
        struct request_data yield_text_contents();
        int factors;
    private slots:
        void add_text_box();
        void reset_factor_stack();
        void change_focus_op(int new_index);
    private:
        QPushButton* operation_button;
        QLineEdit* product_box;
        QLineEdit* final_factor_box;
        QVBoxLayout* factor_stack;
};

class FactorBox : public QFrame {
    public:
        explicit FactorBox(QWidget *parent = 0);
        std::string yield_text_contents();
        void blank_contents();
    private:
        QLineEdit* factor_box;      
};

#endif

