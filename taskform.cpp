#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);
}

TaskForm::TaskForm(TabWidget * t, int i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);
    tab = t;
    ui->gtoaCheck->setChecked(tab->G->getRules().size() != 0);
    ui->gtoaCheck->setDisabled(tab->G->getRules().size() == 0);
    ui->atogCheck->setChecked(tab->A->getInAlphabet().size() != 0);
    ui->atogCheck->setDisabled(tab->A->getInAlphabet().size() == 0);

    ui->label->setText("Язык №" + QString::number(i));
}

TaskForm::~TaskForm()
{
    delete ui;
}

QVector<int> TaskForm::getTaskData()
{
    return {ui->gtoaCheck->isChecked() ? ui->gtoaCoeff->value() : 0,
                ui->atogCheck->isChecked() ? ui->atogCoeff->value() : 0,
                ui->minCheck->isChecked() ? ui->minCoeff->value() : 0,
                ui->detCheck->isChecked() ? ui->detCoeff->value() : 0,
                ui->langCheck->isChecked() ? ui->langCoeff->value() : 0,
                    };
}


void TaskForm::on_gtoaCheck_stateChanged(int arg1)
{
    ui->gtoaCoeff->setDisabled(arg1 == Qt::Unchecked);

    ui->minCheck->setChecked(!(tab->A->getInAlphabet().size() == 0 && arg1 == Qt::Unchecked));
    ui->detCheck->setChecked(!(tab->A->getInAlphabet().size() == 0 && arg1 == Qt::Unchecked));
    ui->langCheck->setChecked(!(tab->A->getInAlphabet().size() == 0 && tab->G->getRules().size() == 0 && arg1 == Qt::Unchecked));

    ui->minCheck->setDisabled(tab->A->getInAlphabet().size() == 0 && arg1 == Qt::Unchecked);
    ui->detCheck->setDisabled(tab->A->getInAlphabet().size() == 0 && arg1 == Qt::Unchecked);
    ui->langCheck->setDisabled(tab->A->getInAlphabet().size() == 0 && tab->G->getRules().size() == 0 && arg1 == Qt::Unchecked);

}


void TaskForm::on_atogCheck_stateChanged(int arg1)
{
    ui->atogCoeff->setDisabled(arg1 == Qt::Unchecked);
    ui->langCheck->setChecked(!(tab->A->getInAlphabet().size() == 0 && tab->G->getRules().size() == 0 && arg1 == Qt::Unchecked));
    ui->langCheck->setDisabled(tab->A->getInAlphabet().size() == 0 && tab->G->getRules().size() == 0 && arg1 == Qt::Unchecked);
}


void TaskForm::on_minCheck_stateChanged(int arg1)
{
    ui->minCoeff->setDisabled(arg1 == Qt::Unchecked);
}


void TaskForm::on_detCheck_stateChanged(int arg1)
{
    ui->detCoeff->setDisabled(arg1 == Qt::Unchecked);
}


void TaskForm::on_langCheck_stateChanged(int arg1)
{
    ui->langCoeff->setDisabled(arg1 == Qt::Unchecked);
}

