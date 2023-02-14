#ifndef ADJMATRIX_H
#define ADJMATRIX_H
#include <QObject>


class AdjMatrix
{
public:
    QVector<QVector<QVector<QString>>> matrix;
    int size;
    AdjMatrix();
    AdjMatrix(const AdjMatrix &M);
    void increaseSize();
    void setSize(int newSize);
    void addAdj(int a, int b, QString s);
    AdjMatrix& operator=(const AdjMatrix &M);
    const QVector<QString> &get(int a, int b) const;

};

#endif // ADJMATRIX_H
