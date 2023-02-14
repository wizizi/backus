#include "adjmatrix.h"
#include <iostream>

AdjMatrix::AdjMatrix()
{
    this->matrix = QVector<QVector<QVector<QString>>>();
    size = 0;
}

void AdjMatrix::increaseSize()
{
    for(int i = 0; i < matrix.size(); i++)
        matrix[i].resize(this->size+1);
    matrix.append(QVector<QVector<QString>>(this->size+1));
    this->size++;
}

void AdjMatrix::setSize(int newSize)
{
    this->matrix.resize(newSize);
    for(int i = 0; i < matrix.size(); i++)
            matrix[i].resize(newSize);
    this->size = newSize;
}

void AdjMatrix::addAdj(int a, int b, QString s)
{
    matrix[a][b].append(s);
}

const QVector<QString> &AdjMatrix::get(int a, int b) const
{
    return this->matrix[a][b];
}

AdjMatrix::AdjMatrix(const AdjMatrix &M)
{
    this->matrix = M.matrix;
}

AdjMatrix& AdjMatrix::operator=(const AdjMatrix &M)
{
    this->matrix = M.matrix;
    return *this;
}
