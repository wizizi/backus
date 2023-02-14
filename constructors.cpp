#include "constructors.h"


QLineEdit * newSymbolInput(QWidget * parent, QString ph, qreal fsize)
{
    QLineEdit * input = new QLineEdit(parent);
    input->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    input->setMaxLength(1);
    input->setPlaceholderText(ph);
    QFont f = QFont("Times New Roman");
    f.setPointSizeF(fsize);
    input->setFont(f);
    input->setMaximumWidth(50);
    input->setMaximumHeight(50);
    return input;
}

