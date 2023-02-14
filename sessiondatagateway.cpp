#include "sessiondatagateway.h"

SessionDataGateway::SessionDataGateway()
{

}

bool SessionDataGateway::saveSession()
{
    QFile loadedFile(loadedFileName);
    loadedFile.remove();
    if(loadedFile.open(QIODevice::WriteOnly))
    {
        QDataStream out(&loadedFile);
        out<<QString("THIS IS A BACKUS SESSION")<<QVector<QVector<QString>>(sessionData);
        sessionSaved = true;
        loadedFile.close();
        return true;
    }
    else return false;
}

bool SessionDataGateway::saveSessionAs(QString filename)
{
    loadedFileName = filename;
    return saveSession();
}

bool SessionDataGateway::loadSession(QString filename)
{
    QFile loadedFile(filename);
    loadedFileName = filename;
    if(loadedFile.open(QIODevice::ReadOnly))
    {
        sessionData.clear();
        QDataStream in(&loadedFile);
        QString check;
        in>>check;
        if(check == "THIS IS A BACKUS SESSION")
        {
            in>>sessionData;
            sessionSaved = true;
            loadedFile.close();
            return true;
        }
        loadedFile.close();
    }
    else return false;
}

void SessionDataGateway::setSessionData(QVector<QVector<QString>> data)
{
    if(data != sessionData) sessionSaved = false;
    sessionData = data;
}

void SessionDataGateway::setTaskData(QVector<QVector<int>> data)
{
    taskData = data;
}


bool SessionDataGateway::sessionIsSaved()
{
    return sessionSaved;
}

void SessionDataGateway::reset()
{
    sessionSaved = true;
    sessionData = {};
    loadedFileName = "";
}

QVector<QVector<QString>> SessionDataGateway::getSessionData()
{
    return sessionData;
}

QString SessionDataGateway::getFileName()
{
    return loadedFileName;
}

bool SessionDataGateway::saveTaskAs(QString filename)
{
    QFile loadedFile(filename);
    loadedFile.remove();
    if(loadedFile.open(QIODevice::WriteOnly))
    {
        QDataStream out(&loadedFile);
        out<<QString("THIS IS A BACKUS TASK")<<QVector<QVector<int>>(taskData)<<QVector<QVector<QString>>(sessionData);
        loadedFile.close();
        return true;
    }
    else return false;
}

bool SessionDataGateway::loadTask(QString filename)
{
    QFile loadedFile(filename);
    if(loadedFile.open(QIODevice::ReadOnly))
    {
        taskData.clear();
        QDataStream in(&loadedFile);
        QString check;
        in>>check;
        if(check == "THIS IS A BACKUS TASK")
        {
            in>>taskData>>sessionData;
            sessionSaved = true;
            loadedFile.close();
            return true;
        }
        loadedFile.close();
    }
    else return false;
}

QVector<QVector<int>> SessionDataGateway::getTaskData()
{
    return taskData;
}
