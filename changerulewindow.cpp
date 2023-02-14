#include "changerulewindow.h"
#include "ui_changerulewindow.h"
#include "rule.cpp"
#include <QMessageBox>
#include "constructors.h"


changeRuleWindow::changeRuleWindow(QString ruleA, QString rulea, QString ruleB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeRuleWindow)
{;
    fontSize = 48;
    ui->setupUi(this);
    a = rulea;
    A = ruleA;
    B = ruleB == "END" ? "" : ruleB;
    initialNT = newSymbolInput(this, A, fontSize);
    initialNT->setText(A);
    ui->ruleInputLayout->addWidget(initialNT);
    arrow = new QLabel(tr("→"), this);
    QFont f = QFont("Times New Roman");
    f.setPointSizeF(fontSize);
    arrow->setFont(f);
    ui->ruleInputLayout->addWidget(arrow);
    resultingT = newSymbolInput(this, a, fontSize);
    resultingT->setText(a);
    ui->ruleInputLayout->addWidget(resultingT);
    resultingNT = newSymbolInput(this, B, fontSize);
    resultingNT->setText(B);
    ui->ruleInputLayout->addWidget(resultingNT);
    ui->ruleInputLayout->setAlignment(Qt::AlignHCenter);
}

changeRuleWindow::~changeRuleWindow()
{
    delete ui;
}

void changeRuleWindow::on_buttonBox_accepted()
{
    if(initialNT->text() != "")
    {
            A = initialNT->text();
            a = resultingT->text();
            B = resultingNT->text();
            this->close();
    }
    else
    {
        QMessageBox err;
        err.setText("Символ слева не может быть пустым.");
        err.exec();
    }
}
