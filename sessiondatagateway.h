#ifndef SESSIONDATAGATEWAY_H
#define SESSIONDATAGATEWAY_H
#include <QDataStream>
#include <QFile>

class SessionDataGateway
{
public:
    SessionDataGateway();
    void setSessionData(QVector<QVector<QString>> data);
    void setTaskData(QVector<QVector<int>> data);
    QVector<QVector<QString>> getSessionData();
    QVector<QVector<int>> getTaskData();
    bool saveSession();
    bool saveSessionAs(QString filename);
    bool loadSession(QString filename);
    bool saveTaskAs(QString filename);
    bool loadTask(QString filename);
    void reset();
    bool sessionIsSaved();
    QString getFileName();

private:
    bool sessionSaved = true;
    QVector<QVector<QString>> sessionData;
    QVector<QVector<int>> taskData;
    QString loadedFileName = "";
};

#endif // SESSIONDATAGATEWAY_H
