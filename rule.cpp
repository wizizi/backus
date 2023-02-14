#include "rule.h"

Rule::Rule(QString X, QString x, QString Y)
{
    this->A = X;
    this->a = x;
    this->B = Y == "" ? "END" : Y;
}

bool Rule::operator==(const Rule &R) const
{
    return (A == R.A) && (a == R.a) && (B == R.B);
}

Rule::Rule(const Rule& R)
{
    this->A = R.A;
    this->a = R.a;
    this->B = R.B;
}
