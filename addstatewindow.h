#ifndef ADDSTATEWINDOW_H
#define ADDSTATEWINDOW_H

#include <QDialog>
#include "automatonfield.h"

namespace Ui {
class addStateWindow;
}

class addStateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addStateWindow(QWidget *parent = nullptr);
    addStateWindow(QWidget *parent, automatonField *af, QPoint pos);
    ~addStateWindow();

private slots:
    void on_buttonBox_accepted();

private:
    QPoint position;
    automatonField *aField;
    Ui::addStateWindow *ui;
};

#endif // ADDSTATEWINDOW_H
