#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include "grammar.h"
#include "automaton.h"
#include "transformations.h"
#include "addstatewindow.h"
#include "tabwidget.h"
#include "regexeqsys.h"
#include "sessiondatagateway.h"
#include "taskeditorwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void filenameNotSet(bool set);

private slots:
    void closeTab(int index);
    void on_tabWidget_currentChanged(int index);
    void newSession();
    void loadSession();
    void saveSession();
    void saveSessionAs();
    void editTask();
    void loadTask();

private:
    bool inTaskMode = false;
    int maxPoints = 0;
    int currentPoints = 0;
    qreal grade = 0;
    QTabWidget * tabs;
    QVector<TabWidget *> languages;
    QVector<QVector<QString>> compileSessionData();
    bool suggestSave();
    void decompileSessionData(QVector<QVector<QString>> data);
    void endTask();
    SessionDataGateway gate = SessionDataGateway();
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
