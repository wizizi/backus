#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "adjmatrix.h"
#include "state.h"
#include "grammar.h"
#include <QObject>

class Automaton:QObject
{
public:
    Automaton();
    bool addState(QString S);
    void deleteState(QString S);
    void deleteConn(QString iniState, QString symbol, QString finState);
    void setFinality(QString S, bool finality);
    void changeName(QString oldName, QString newName);
    bool addSymbol(QString S);
    bool addConnection(QString iniState, QString symbol, QString finState);
    void determineAutomaton();
    void minimizeAutomaton();
    QVector<QVector<QVector<int>>> getTransMatrix();


    const QVector<QString> &getExAlphabet() const;
    void setExAlphabet(const QVector<QString> &newExAlphabet);

    const QVector<State> &getInAlphabet() const;
    void setInAlphabet(const QVector<State> &newInAlphabet);

    const AdjMatrix &getConnections() const;
    void setConnections(const AdjMatrix &newConnections);

private:
    QVector<QString> exAlphabet;
    QVector<State> inAlphabet;
    AdjMatrix connections;

    void restructureStates(QVector<int> states, QVector<QVector<QVector<int>>> transMatrix, AdjMatrix * newConnections, QVector<QVector<int>> * stateClasses);
};

#endif // AUTOMATON_H
