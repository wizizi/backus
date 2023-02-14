#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "grammar.h"
#include "automaton.h"
#include "transformations.h"
#include "addstatewindow.h"
#include "regexeqsys.h"
#include <QMessageBox>

namespace Ui {
class TabWidget;
}

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    TabWidget(QWidget *parent = nullptr);
    void load();
    void startTask(QVector<int> data);
    Grammar * G;
    Automaton * A;
    ~TabWidget();


private slots:
    void on_addRuleButton_clicked();

    void on_buttonGtoA_clicked();

    void on_buttonAtoG_clicked();

    void on_buttonDetermine_clicked();

    void on_buttonMinimize_clicked();

    void on_clearButton_clicked();

    void on_grammarView_itemDoubleClicked(QListWidgetItem *item);

    void on_examineButton_clicked();

private:
    bool inTaskMode = false;
    QVector<int> taskConfig;
    int maxPoints = 0;
    int currentPoints = 0;
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void updateLanguage();
    void calculateResult();
    Ui::TabWidget *ui;

};

#endif // TABWIDGET_H
