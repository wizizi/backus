#ifndef REGEXEQSYS_H
#define REGEXEQSYS_H
#include <QString>
#include <QVector>
#include "grammar.h"


class RegexEqTerm
{
public:
    RegexEqTerm();
    RegexEqTerm(QString rex, QString nt);
    QString toString() const;
    QString getRegex() const;
    QString getNT() const;
    void setRegex(QString rex);

private:
    QString NT = "";
    QString rEx = "";

};

class RegexEq
{
public:
    RegexEq();
    RegexEq(QVector<QString> variables, QString NT, QVector<Rule> rules);
    QString toString() const;
    QString getCoeff(QString nt) const;
    QString getSelfCoeff() const;
    QString getNT() const;
    QString getFreeTerm() const;
    void remove(QString nt);
    void plug(const RegexEq &);
private:
    QVector<QString> variables;
    QString NT;
    QVector<RegexEqTerm> terms;
    QString freeTerm = "";

};

class RegexEqSys
{
public:
    RegexEqSys();
    RegexEqSys(const Grammar &G);
    QString toString() const;
    QString solve();

private:
    QVector<RegexEq> equations;
};

#endif // REGEXEQSYS_H
