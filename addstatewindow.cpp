#include "addstatewindow.h"
#include <iostream>
#include "ui_addstatewindow.h"

addStateWindow::addStateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStateWindow)
{
    ui->setupUi(this);
}

addStateWindow::addStateWindow(QWidget *parent, automatonField *af, QPoint pos) :
    QDialog(parent),
    ui(new Ui::addStateWindow)
{
    aField = af;
    position = pos;
    ui->setupUi(this);

}

addStateWindow::~addStateWindow()
{
    delete ui;
}

void addStateWindow::on_buttonBox_accepted()
{

    aField->addState(position, ui->nameEdit->text(), ui->isFinalBox->isChecked());
    aField = nullptr;
    this->close();
}


void automatonField::openAddStateWindow(QPoint pos)
{
    addStateWindow d = addStateWindow(this, this, pos);
    d.exec();
}

