#include "grammar.h"

Grammar::Grammar()
{
    this->tAlphabet = QVector<QString>();
    this->ntAlphabet = QVector<QString>();
    this->rules = QVector<Rule>();
}

Grammar::Grammar(QVector<QString> ntA, QVector<QString> tA, QVector<QString> r)
{
    this->tAlphabet = tA;
    this->ntAlphabet = ntA;
    this->rules = QVector<Rule>();
    for(int i = 0; i < r.size(); i+=3) addRule(Rule(r[i], r[i+1], r[i+2]));
}

const QVector<QString> &Grammar::getNtAlphabet() const
{
    return ntAlphabet;
}

void Grammar::setNtAlphabet(const QVector<QString> &newNtAlphabet)
{
    ntAlphabet = newNtAlphabet;
}

const QVector<QString> &Grammar::getTAlphabet() const
{
    return tAlphabet;
}

void Grammar::setTAlphabet(const QVector<QString> &newTAlphabet)
{
    tAlphabet = newTAlphabet;
}




QVector<Rule> Grammar::altRules(QString NT) const
{
    QVector<Rule> res = {};
    for(int i = 0; i < rules.size(); i++)
        if(rules[i].A == NT)
            res.append(rules[i]);
    return res;
}


bool Grammar::addT(QString T)
{
    if(!this->ntAlphabet.contains(T))
    {
        if(!this->tAlphabet.contains(T) && T != "")
        {
            this->tAlphabet.append(T);
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Grammar::addNT(QString NT)
{
    if(!this->tAlphabet.contains(NT))
    {
        if(!this->ntAlphabet.contains(NT) && NT != "" && NT != "END")
        {
            this->ntAlphabet.append(NT);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Grammar::addRule(Rule R)
{
    bool i = this->addNT(R.A);
    bool j = this->addT(R.a);
    bool k = this->addNT(R.B);
    if(i && j && k)
    {
        this->rules.append(R);
    }
}

void Grammar::changeRule(int i, Rule R)
{
    QString A = rules[i].A;
    bool AStays = false;
    QString B = rules[i].B;
    bool BStays = false;
    addNT(R.A);
    addT(R.a);
    addNT(R.B);
    rules[i].A = R.A;
    rules[i].a = R.a;
    rules[i].B = R.B;
    for(int j = 0; j < rules.size(); j++)
    {
        AStays = AStays || rules[j].A == A || rules[j].B == A || A == "END";
        BStays = BStays || rules[j].A == B || rules[j].B == B || B == "END";
    }
    if(!AStays) ntAlphabet.remove(ntAlphabet.indexOf(A));
    if(!BStays) ntAlphabet.remove(ntAlphabet.indexOf(B));
}

void Grammar::removeRule(int i)
{
    QString A = rules[i].A;
    bool AStays = false;
    QString B = rules[i].B;
    bool BStays = false;
    rules.remove(i);
    for(int j = 0; j < rules.size(); j++)
    {
        AStays = AStays || rules[j].A == A || rules[j].B == A || A == "END";
        BStays = BStays || rules[j].A == B || rules[j].B == B || B == "END";
    }
    if(!AStays) ntAlphabet.remove(ntAlphabet.indexOf(A));
    if(!BStays) ntAlphabet.remove(ntAlphabet.indexOf(B));
}

QStringList Grammar::ruleList()
{
    QStringList res;
    for(int i = 0; i < this->rules.size(); i++)
    {
        QString X = this->rules[i].A;
        QString x = this->rules[i].B == "END" && this->rules[i].a == "" ? "λ" : this->rules[i].a;
        QString Y = this->rules[i].B == "END" ? "" : this->rules[i].B;
        res.append(X + " → " + x + Y);
    }
    return res;
}

const QVector<Rule> &Grammar::getRules() const
{
    return rules;
}

void Grammar::setRules(const QVector<Rule> &newRules)
{
    rules = newRules;
}


QVector<QString> Grammar::compileRules()
{
    QVector<QString> res = {};
    for(int i = 0; i < rules.size(); i++)
    {
        res.append(rules[i].A);
        res.append(rules[i].a);
        res.append(rules[i].B);
    }
    return res;

}
