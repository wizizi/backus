#include "addconnwindow.h"
#include "ui_addconnwindow.h"

addConnWindow::addConnWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addConnWindow)
{
    ui->setupUi(this);
}

addConnWindow::addConnWindow(QWidget *parent, Automaton * aut, QString s1, QString s2) :
    QDialog(parent),
    ui(new Ui::addConnWindow)
{
    iniState = s1;
    resState = s2;
    A = aut;
    ui->setupUi(this);
}

addConnWindow::~addConnWindow()
{
    delete ui;
}


void addConnWindow::on_buttonBox_accepted()
{
    A->addConnection(iniState, ui->connSymbEdit->text(), resState);
    this->close();
}

