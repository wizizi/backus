#include "addrulewindow.h"
#include "ui_addrulewindow.h"
#include "rule.h"
#include <QMessageBox>
#include "constructors.h"


addRuleWindow::addRuleWindow(QWidget *parent, Grammar *Gr) :
    QDialog(parent),
    ui(new Ui::addRuleWindow)
{
    ruleAmount = 1;
    fontSize = 48;
    this->G = Gr;
    ui->setupUi(this);
    initialNT = newSymbolInput(this, "A", fontSize);
    ui->ruleInputLayout->addWidget(initialNT);
    arrow = new QLabel(tr("→"), this);
    QFont f = QFont("Times New Roman");
    f.setPointSizeF(fontSize);
    arrow->setFont(f);
    ui->ruleInputLayout->addWidget(arrow);
    resultingTs.append(newSymbolInput(this, "a", fontSize));
    ui->ruleInputLayout->addWidget(resultingTs[0]);
    resultingNTs.append(newSymbolInput(this, "B", fontSize));
    ui->ruleInputLayout->addWidget(resultingNTs[0]);
    ui->ruleInputLayout->setAlignment(Qt::AlignHCenter);
}

addRuleWindow::~addRuleWindow()
{
    delete ui;
}

void addRuleWindow::on_buttonBox_accepted()
{
    if(initialNT->text() != "")
    {
        for(int i = 0; i < ruleAmount; i++)
        {
            G->addRule(Rule(initialNT->text(), resultingTs[i]->text(), resultingNTs[i]->text()));
            this->close();
        }
    }
    else
    {
        QMessageBox err;
        err.setText("Символ слева не может быть пустым.");
        err.exec();
    }
}


void addRuleWindow::on_orButton_clicked()
{
    fontSize = fontSize * ((2.0*ruleAmount + 1.0)/(2.0*ruleAmount + 3.0));
    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(ui->ruleInputLayout->layout());
    ors.append(new QLabel(tr("|"), this));
    layout->addWidget(ors.last());
    resultingTs.append(newSymbolInput(this, "a", fontSize));
    layout->addWidget(resultingTs.last());
    resultingNTs.append(newSymbolInput(this, "B", fontSize));
    layout->addWidget(resultingNTs.last());
    QFont f = QFont("Times New Roman");
    f.setPointSizeF(fontSize);
    initialNT->setFont(f);
    arrow->setFont(f);
    for(int i = 0; i < ruleAmount; i++)
    {
        resultingNTs[i]->setFont(f);
        resultingTs[i]->setFont(f);
    }

    ruleAmount++;
}

