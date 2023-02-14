#ifndef CHANGERULEWINDOW_H
#define CHANGERULEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "grammar.h"

namespace Ui {
class changeRuleWindow;
}

class changeRuleWindow : public QDialog
{
    Q_OBJECT

public:
    QString A;
    QString a;
    QString B;
    explicit changeRuleWindow(QString ruleA, QString rulea, QString ruleB, QWidget *parent = nullptr);
    ~changeRuleWindow();

private slots:
    void on_buttonBox_accepted();


private:
    QLineEdit * initialNT;
    QLineEdit * resultingT;
    QLineEdit * resultingNT;
    QLabel * arrow;
    Ui::changeRuleWindow *ui;
    qreal fontSize;
};

#endif // CHANGERULEWINDOW_H
