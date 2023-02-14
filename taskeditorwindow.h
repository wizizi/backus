#ifndef TASKEDITORWINDOW_H
#define TASKEDITORWINDOW_H

#include <QDialog>
#include "taskform.h"

namespace Ui {
class TaskEditorWindow;
}

class TaskEditorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TaskEditorWindow(QWidget *parent = nullptr);
    explicit TaskEditorWindow(QVector<TabWidget *> langs, QWidget *parent = nullptr);
    QVector<QVector<int>> getTaskData();
    ~TaskEditorWindow();

private:
    QVector<TaskForm *> tabs;
    Ui::TaskEditorWindow *ui;
};

#endif // TASKEDITORWINDOW_H
