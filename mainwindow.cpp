#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addrulewindow.h"
#include "changerulewindow.h"
#include "automatonfield.h"
#include <QGridLayout>
#include "transformations.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabs = new QTabWidget(this);
    TabWidget * tab1 = new TabWidget(tabs);
    TabWidget * tab2 = new TabWidget(tabs);
    tabs->addTab(tab1, "Язык №&1");
    tabs->addTab(tab2, "Добавить язык");
    tabs->setTabsClosable(true);
    tabs->tabBar()->tabButton(1, QTabBar::RightSide)->hide();
    ui->mainLayout->addWidget(tabs);
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    languages.append(tab1);
    languages.append(tab2);

    QMenu * fileMenu = menuBar()->addMenu("Файл");
    QAction * newAction = new QAction("Новая сессия");
    connect(newAction, &QAction::triggered, this, &MainWindow::newSession);
    QAction * loadAction = new QAction("Открыть");
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadSession);
    QAction * saveAction = new QAction("Сохранить");
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveSession);
    connect(this, &MainWindow::filenameNotSet, saveAction, &QAction::setDisabled);
    QAction * saveAsAction = new QAction("Сохранить как...");
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveSessionAs);
    fileMenu->addAction(newAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    filenameNotSet(true);

    QMenu * taskMenu = menuBar()->addMenu("Задание");
    QAction * editTaskAction = new QAction("Редактор заданий");
    connect(editTaskAction, &QAction::triggered, this, &MainWindow::editTask);
    QAction * loadTaskAction = new QAction("Начать задание");
    connect(loadTaskAction, &QAction::triggered, this, &MainWindow::loadTask);
    taskMenu->addAction(editTaskAction);
    taskMenu->addAction(loadTaskAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == tabs->count() - 1 && !inTaskMode)
    {
        TabWidget * newtab = new TabWidget(tabs);
        tabs->setTabText(index, "Язык №&" + QString::number(tabs->count()));
        tabs->tabBar()->tabButton(index, QTabBar::RightSide)->show();
        std::cout << tabs->addTab(newtab, "Добавить язык") << std::endl;
        tabs->tabBar()->tabButton(tabs->count() - 1, QTabBar::RightSide)->hide();
        languages.append(newtab);
    }
}

void MainWindow::closeTab(int index)
{
    if(index > 0) tabs->setCurrentIndex(index-1);
    std::cout << "Removal requested." << std::endl;
    languages.remove(index);
    tabs->removeTab(index);
    for(int i = 0; i < tabs->count() - 1; i++) tabs->setTabText(i, "Язык №&" + QString::number(i+1));
}


QVector<QVector<QString>> MainWindow::compileSessionData()
{
    QVector<QVector<QString>> sessionData = {};
    for(int i = 0; i < languages.size() - 1; i++)
    {
        sessionData.append(languages[i]->G->getNtAlphabet());
        sessionData.append(languages[i]->G->getTAlphabet());
        sessionData.append(languages[i]->G->compileRules());
        Grammar * tempG = AutomatonToGrammar(*(languages[i]->A));
        sessionData.append(tempG->getNtAlphabet());
        sessionData.append(tempG->getTAlphabet());
        sessionData.append(tempG->compileRules());
        delete tempG;
    }
    return sessionData;
}

void MainWindow::decompileSessionData(QVector<QVector<QString>> data)
{
    tabs->close();
    languages.clear();
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    ui->mainLayout->addWidget(tabs);
    std::cout << "TACTICAL NUKE INCOMING" << std::endl;
    std::cout << data[3].size() << std::endl;
    std::cout << "TACTICAL NUKE INCOMING" << std::endl;
    for(int i = 0; i < data.size(); i+=6)
    {
        TabWidget * newtab = new TabWidget(tabs);
        std::cout << tabs->addTab(newtab, "Язык №&" + QString::number(1 + i/6)) << std::endl;
        languages.append(newtab);
        delete newtab->A;
        delete newtab->G;
        newtab->G = new Grammar(data[i], data[i+1], data[i+2]);
        newtab->A = GrammarToAutomaton(Grammar(data[i+3], data[i+4], data[i+5]));
        std::cout << "TACTICAL NUKE INCOMING" << std::endl;
        newtab->load();
    }
    TabWidget * newtab = new TabWidget(tabs);
    std::cout << tabs->addTab(newtab, "Добавить язык") << std::endl;
    tabs->tabBar()->tabButton(tabs->count() - 1, QTabBar::RightSide)->hide();
    languages.append(newtab);
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

void MainWindow::newSession()
{
    gate.setSessionData(compileSessionData());
    if(!gate.sessionIsSaved())
        if(!suggestSave()) return;
    gate.reset();
    filenameNotSet(true);
    tabs->close();
    languages.clear();
    tabs = new QTabWidget(this);
    TabWidget * tab1 = new TabWidget(tabs);
    TabWidget * tab2 = new TabWidget(tabs);
    tabs->addTab(tab1, "Язык №&1");
    tabs->addTab(tab2, "Добавить язык");
    tabs->setTabsClosable(true);
    tabs->tabBar()->tabButton(1, QTabBar::RightSide)->hide();
    ui->mainLayout->addWidget(tabs);
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    languages.append(tab1);
    languages.append(tab2);
    std::cout << "Tabs:" << languages.size() << std::endl;
}

bool MainWindow::suggestSave()
{
    QMessageBox sugg = QMessageBox(QMessageBox::Question, "Сохранение сессии", "Сохранить сессию?", {QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel}, this);
    int result = sugg.exec();
    if(result == QMessageBox::Discard) return true;
    if(result == QMessageBox::Cancel) return false;
    if(result == QMessageBox::Save)
    {
        if(gate.getFileName() != "")
            saveSession();
        else
            saveSessionAs();
        return true;
    }

}


void MainWindow::loadSession()
{
    gate.setSessionData(compileSessionData());
    if(!gate.sessionIsSaved())
        if(!suggestSave()) return;
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть сессию", "C:/", "(*.bsf)");
    if(fileName != "")
    {
        if(gate.loadSession(fileName)) filenameNotSet(false);
        decompileSessionData(gate.getSessionData());
    }
}


void MainWindow::saveSession()
{
    gate.setSessionData(compileSessionData());
    gate.saveSession();

}

void MainWindow::saveSessionAs()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить сессию", "C:/", "(*.bsf)");
    if(fileName != "")
    {
        gate.setSessionData(compileSessionData());
        if(gate.saveSessionAs(fileName)) filenameNotSet(false);
    }

}

void MainWindow::editTask()
{
    TaskEditorWindow ed = TaskEditorWindow(languages, this);
    int res = ed.exec();
    if(res == QDialog::Accepted)
    {
        std::cout << "Data:" << ed.getTaskData().size() << std::endl;
        gate.setTaskData(ed.getTaskData());
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить вариант", "C:/", "(*.btf)");
        gate.setSessionData(compileSessionData());
        gate.saveTaskAs(fileName);
    }
}

void MainWindow::loadTask()
{
    gate.setSessionData(compileSessionData());
    if(!gate.sessionIsSaved())
        if(!suggestSave()) return;
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть задание", "C:/", "(*.btf)");
    if(fileName != "")
    {
        if(gate.loadTask(fileName))
            decompileSessionData(gate.getSessionData());
        languages.remove(tabs->count() - 1);
        tabs->removeTab(tabs->count() - 1);
        QVector<QVector<int>> taskData = gate.getTaskData();
        inTaskMode = true;
        menuBar()->setDisabled(true);
        for(int i = 0; i < taskData.size(); i++)
        {
            languages[i]->startTask(taskData[i]);
            tabs->tabBar()->tabButton(i, QTabBar::RightSide)->hide();
            for(int j = 0; j < taskData[i].size(); j++)
            {
                maxPoints+=taskData[i][j];
            }
        }

    }
}
