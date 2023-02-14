#include "taskeditorwindow.h"
#include "ui_taskeditorwindow.h"

TaskEditorWindow::TaskEditorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskEditorWindow)
{
    ui->setupUi(this);
}

TaskEditorWindow::TaskEditorWindow(QVector<TabWidget *> langs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskEditorWindow)
{
    ui->setupUi(this);
    for(int i = 0; i < langs.size() - 1; i++)
    {
        tabs.append(new TaskForm(langs[i], i, this));
        ui->mainLayout->addWidget(tabs[i]);
    }

}
TaskEditorWindow::~TaskEditorWindow()
{
    delete ui;
}

QVector<QVector<int>> TaskEditorWindow::getTaskData()
{
    QVector<QVector<int>> res;
    for(int i = 0; i < tabs.size(); i++)
        res.append(tabs[i]->getTaskData());
    return res;
}
