#ifndef ADDRULEWINDOW_H
#define ADDRULEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "grammar.h"

namespace Ui {
class addRuleWindow;
}

class addRuleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addRuleWindow(QWidget *parent = nullptr, Grammar * Gr = new Grammar());
    Grammar * G;
    ~addRuleWindow();

private slots:
    void on_buttonBox_accepted();
    void on_orButton_clicked();
    //void startNextInput();

private:
    QLineEdit * initialNT;
    QVector<QLineEdit *> resultingTs;
    QVector<QLineEdit *> resultingNTs;
    QLabel * arrow;
    QVector<QLabel *> ors;
    Ui::addRuleWindow *ui;
    int ruleAmount;
    qreal fontSize;
};

#endif // ADDRULEWINDOW_H
