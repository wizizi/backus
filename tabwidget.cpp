#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "addrulewindow.h"
#include "changerulewindow.h"
#include "automatonfield.h"
#include <QGridLayout>
#include <iostream>

TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWidget)
{
    G = new Grammar();
    A =  new Automaton();
    ui->setupUi(this);
    ui->examineButton->hide();
    ui->taskText->hide();
    this->setLayout(ui->mainLayout);
    ui->Canvas->A = this->A;
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::on_addRuleButton_clicked()
{
    addRuleWindow d = addRuleWindow(this, G);
    d.exec();
    ui->grammarView->clear();
    ui->grammarView->addItems(G->ruleList());
    for(int i = 0; i < G->getRules().size(); i++)
    {
        ui->grammarView->item(i)->setData(1, i);
    }
    if(G != nullptr) updateLanguage();
}

void TabWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete && ui->grammarView->currentItem() != nullptr)
    {
            std::cout << "Removing rule #" << ui->grammarView->currentItem()->data(1).toInt() << std::endl;
            G->removeRule((ui->grammarView->currentItem()->data(1).toInt()));
            QListWidgetItem *it = ui->grammarView->takeItem(ui->grammarView->currentRow());
            delete it;
            if(G != nullptr)
            {
                RegexEqSys res = RegexEqSys(*G);
                ui->langDisplay->setText("Язык: " + res.solve());
            }
    }
}


void TabWidget::on_buttonGtoA_clicked()
{
    delete A;
    //delete ui->Canvas->A;
    A = GrammarToAutomaton(*G);
    ui->Canvas->A = this->A;
    ui->Canvas->updateVertices();
    this->update();
}



void TabWidget::on_buttonAtoG_clicked()
{
    delete G;
    G = AutomatonToGrammar(*A);
    ui->grammarView->clear();
    ui->grammarView->addItems(G->ruleList());
    for(int i = 0; i < G->getRules().size(); i++)
    {
        ui->grammarView->item(i)->setData(1, i);
    }
    if(G != nullptr) updateLanguage();

}


void TabWidget::on_buttonDetermine_clicked()
{
    ui->Canvas->clearVertices();
    A->determineAutomaton();
    ui->Canvas->updateVertices();
    this->update();
}


void TabWidget::on_buttonMinimize_clicked()
{
    ui->Canvas->clearVertices();
    A->minimizeAutomaton();
    ui->Canvas->updateVertices();
    this->update();
}


void TabWidget::on_clearButton_clicked()
{
    ui->grammarView->clear();
    delete A;
    delete G;
    G = new Grammar();
    A = new Automaton();
    ui->Canvas->A = this->A;
    ui->Canvas->updateVertices();
    ui->langDisplay->setText("");
    this->update();
}


void TabWidget::on_grammarView_itemDoubleClicked(QListWidgetItem *item)
{
    Rule oldRule = G->getRules()[item->data(1).toInt()];
    changeRuleWindow d = changeRuleWindow(oldRule.A, oldRule.a, oldRule.B, this);
    d.exec();
    G->changeRule(item->data(1).toInt(), Rule(d.A, d.a, d.B));
    ui->grammarView->clear();
    ui->grammarView->addItems(G->ruleList());
    for(int i = 0; i < G->getRules().size(); i++)
    {
        ui->grammarView->item(i)->setData(1, i);
    }
    if(G != nullptr) updateLanguage();
}

void TabWidget::paintEvent(QPaintEvent *event)
{
    QPainter *paint = new QPainter(this);
    paint->setBrush(QBrush(QColor(242,242,242)));
    paint->setPen(QColorConstants::Transparent);
    paint->drawRect(0, 0, this->width(), this->height());
    paint->end();
}

void TabWidget::updateLanguage()
{
    if(!inTaskMode)
    {
        RegexEqSys res = RegexEqSys(*G);
        ui->langDisplay->setText("Язык: " + res.solve());
    }
}


void TabWidget::load()
{
    ui->Canvas->A = this->A;
    ui->Canvas->updateVertices();
    ui->Canvas->repaint();
    ui->grammarView->addItems(G->ruleList());
    for(int i = 0; i < G->getRules().size(); i++)
        ui->grammarView->item(i)->setData(1, i);
    updateLanguage();
}


void TabWidget::startTask(QVector<int> data)
{
    inTaskMode = true;
    taskConfig = data;
    ui->examineButton->show();
    ui->taskText->show();
    QString taskDescription = "Ваше задание:\n";
    for(int i = 0; i < data.size(); i++)
        maxPoints += data[i];
    if(data[0] > 0) taskDescription += "Постройте автомат\n";
    if(data[1] > 0) taskDescription += "Постройте грамматику\n";
    if(data[2] > 0) taskDescription += "Минимизируйте автомат\n";
    if(data[3] > 0) taskDescription += "Детерминируйте автомат\n";
    if(data[4] > 0)
    {
        taskDescription += "Определите язык\n";
        ui->langDisplay->setReadOnly(false);
        ui->langDisplay->setPlaceholderText("Введите язык здесь");
    }
    ui->langDisplay->setText("");
    ui->taskText->setText(taskDescription);
    ui->buttonMinimize->hide();
    ui->buttonDetermine->hide();
    ui->buttonAtoG->hide();
    ui->buttonGtoA->hide();
}

void TabWidget::on_examineButton_clicked()
{
    QMessageBox sugg = QMessageBox(QMessageBox::Question, "Результаты", "Ваша оценка: 70/100", {QMessageBox::Ok}, this);
    sugg.exec();
}

