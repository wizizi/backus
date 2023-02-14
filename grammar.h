#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <QVector>
#include "rule.h"
#include "automaton.h"
#include <QObject>

class Grammar:QObject
{

public:
    Grammar();
    Grammar(QVector<QString> ntA, QVector<QString> tA, QVector<QString> r);
    QVector<Rule> altRules(QString NT) const;
    bool addT(QString T);
    bool addNT(QString NT);
    void addRule(Rule R);
    void changeRule(int i, Rule newR);
    void removeRule(int i);
    QVector<QString> compileRules();
    //Grammar& operator=(const Automaton &G);
    QStringList ruleList();
    const QVector<QString> &getTAlphabet() const;
    void setTAlphabet(const QVector<QString> &newTAlphabet);
    const QVector<QString> &getNtAlphabet() const;
    void setNtAlphabet(const QVector<QString> &newNtAlphabet);
    const QVector<Rule> &getRules() const;
    void setRules(const QVector<Rule> &newRules);

private:
    QVector<QString> tAlphabet;
    QVector<QString> ntAlphabet;
    QVector<Rule> rules;

};

#endif // GRAMMAR_H
