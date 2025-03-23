#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "wordboxbox.h"

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class QComboBox;
class Window : public QWidget
{
 public:
  explicit Window(QWidget *parent = 0);
 private:
 QComboBox *operation_combo_box;
 QComboBox *word_count_combo_box;
 QPushButton *reset_button;
 QPushButton *go_button;
 QHBoxLayout *main_split_layout;
 QScrollArea *solution_scroll_area;
 QVBoxLayout *left_stack_layout;
 ArithBox *arithmetic_args_box;
};

#endif // WINDOW_H