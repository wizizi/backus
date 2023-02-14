#ifndef ADDCONNWINDOW_H
#define ADDCONNWINDOW_H

#include <QDialog>
#include "automaton.h"

namespace Ui {
class addConnWindow;
}

class addConnWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addConnWindow(QWidget *parent = nullptr);
    addConnWindow(QWidget *parent, Automaton * A, QString s1, QString s2);
    ~addConnWindow();

private slots:
    void on_buttonBox_accepted();

private:
    QString iniState;
    QString resState;
    Automaton * A;
    Ui::addConnWindow *ui;
};

#endif // ADDCONNWINDOW_H
