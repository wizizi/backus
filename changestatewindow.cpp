#include "changestatewindow.h"
#include <iostream>
#include "ui_changestatewindow.h"

changeStateWindow::changeStateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeStateWindow)
{
    ui->setupUi(this);
}

changeStateWindow::changeStateWindow(QWidget *parent, automatonField *af, QString name, bool fin) :
    QDialog(parent),
    ui(new Ui::changeStateWindow)
{
    aField = af;
    iniFin = fin;
    iniName = name;
    ui->setupUi(this);
    ui->nameEdit->setText(name);
    ui->isFinalBox->setChecked(fin);

}

changeStateWindow::~changeStateWindow()
{
    delete ui;
}

void changeStateWindow::on_buttonBox_accepted()
{

    aField->changeState(iniName, ui->nameEdit->text(), ui->isFinalBox->isChecked());
    aField = nullptr;
    this->close();
}

void automatonField::openChangeStateWindow(QString name, bool fin)
{
    changeStateWindow d = changeStateWindow(this, this, name, fin);
    d.exec();
}




