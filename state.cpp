#include "state.h"

State::State(const QString &S)
{
    this->name = S;
    this->isFinal = false;
}

State::State(const QString &S, bool F)
{
    this->name = S;
    this->isFinal = F;
}

State::State(const State &S)
{
    this->name = S.name;
    this->isFinal = S.isFinal;
}


State& State::operator=(const QString &S)
{
    this->name = S;
    return *this;
}


State& State::operator=(const State &S)
{
    this->name = S.name;
    this->isFinal = S.isFinal;
    return *this;
}

bool State::operator==(const QString &S) const
{
    return this->name == S;
}

bool State::operator==(const State &S) const
{
    return this->name == S.name;
}
