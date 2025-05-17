#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "qfinder.h"
#include "wordboxbox.h"
#include "filebox.h"

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class QComboBox;
class Window : public QWidget
{
    Q_OBJECT
    public:
    explicit Window(QWidget *parent = 0);

    signals:
    void request_data_ready(request_data req);

    private slots:
    void slot_calculate_request();
    void slot_populate_solution_area();

    private:
    QComboBox *operation_combo_box;
    QComboBox *word_count_combo_box;
    QPushButton *reset_button;
    QPushButton *go_button;
    QHBoxLayout *main_split_layout;
    QScrollArea *solution_scroll_area;
    QVBoxLayout *right_word_list_stack_layout;
    QVBoxLayout *left_stack_layout;
    ArithBox *arithmetic_args_box;
    FileSelectBox *file_select_box;

    QFinder *my_q_finder;
};

#endif // WINDOW_H