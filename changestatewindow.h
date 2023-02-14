#ifndef ADDSTATEWINDOW_H
#define ADDSTATEWINDOW_H

#include <QDialog>
#include "automatonfield.h"

namespace Ui {
class changeStateWindow;
}

class changeStateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit changeStateWindow(QWidget *parent = nullptr);
    changeStateWindow(QWidget *parent, automatonField *af, QString name, bool fin);
    ~changeStateWindow();

private slots:
    void on_buttonBox_accepted();

private:
    QString iniName;
    bool iniFin;
    automatonField *aField;
    Ui::changeStateWindow *ui;
};

#endif // ADDSTATEWINDOW_H
