#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "tabwidget.h"

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = nullptr);
    explicit TaskForm(TabWidget * t, int i, QWidget *parent = nullptr);
    QVector<int> getTaskData();
    ~TaskForm();

private slots:
    void on_gtoaCheck_stateChanged(int arg1);

    void on_atogCheck_stateChanged(int arg1);

    void on_minCheck_stateChanged(int arg1);

    void on_detCheck_stateChanged(int arg1);

    void on_langCheck_stateChanged(int arg1);

private:
    TabWidget * tab;
    Ui::TaskForm *ui;
};

#endif // TASKFORM_H
