#ifndef RULE_H
#define RULE_H
#include <QVector>
#include <QObject>

class Rule
{
public:
    QString A;
    QString a;
    QString B;
    bool operator==(const Rule &R) const;
    Rule(const Rule&);
    Rule(QString X, QString x, QString Y);
};

#endif // RULE_H
