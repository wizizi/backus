#ifndef STATE_H
#define STATE_H
#include <QString>

class State
{
public:
    bool isFinal;
    QString name;
    State(const QString &S);
    State(const QString &S, bool F);
    State(const State &S);
    State& operator=(const State &S);
    State& operator=(const QString &S);
    bool operator==(const State &S) const;
    bool operator==(const QString &S) const;

};

#endif // STATE_H
