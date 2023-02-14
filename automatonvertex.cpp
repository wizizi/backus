#include "automatonvertex.h"
#include "ui_automatonvertex.h"
#include <QPainter>
#include <iostream>



automatonVertex::automatonVertex(QWidget *parent, int size, QString sN, bool isF) :
    QLabel(parent),
    ui(new Ui::automatonVertex)
{
    stateName = sN;
    isFinal = isF;
    this->setFixedSize(size, size);
    vertexMask = new QRectF(this->width()/4, this->width()/4, this->width()/2, this->height()/2);
    updatePixmap();
    ui->setupUi(this);
}

void automatonVertex::updatePixmap()
{
    QPixmap * pix = new QPixmap(this->width(), this->height());
    pix->fill(Qt::transparent);
    QPainter *paintPix = new QPainter(pix);
    QRectF vertexImage = QRectF(this->width()/4, this->width()/4, this->width()/2, this->height()/2);
    if(selected)
    {
        QPen selectPen = QPen(QBrush(Qt::black), 1);
        selectPen.setColor(Qt::black);
        selectPen.setStyle(Qt::DotLine);
        paintPix->setPen(selectPen);
        paintPix->drawRect(vertexImage);
    }
    QPen pen = QPen(QBrush(Qt::gray), 3);
    pen.setColor(Qt::black);
    paintPix->setPen(pen);
    paintPix->setBrush(QBrush(Qt::white));
    paintPix->setBackground(QBrush(Qt::white));
    paintPix->drawEllipse(vertexImage);
    QFont f = QFont("Times New Roman", 2*vertexImage.height()/5);
    paintPix->setFont(f);
    paintPix->drawText(vertexImage.x() + vertexImage.width()/2, vertexImage.y(), stateName);
    f = QFont("Times New Roman", vertexImage.height()/2);
    paintPix->setFont(f);
    if(this->isFinal)
        paintPix->drawText(vertexImage.x()+1*vertexImage.width()/3, vertexImage.y()+3*vertexImage.height()/4, "#");
    this->setPixmap(*pix);
    paintPix->end();
}

automatonVertex::automatonVertex(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::automatonVertex)
{
    ui->setupUi(this);
}

automatonVertex::~automatonVertex()
{
    delete ui;
}

void automatonVertex::paintEvent(QPaintEvent *event)
{
    std::cout << this->stateName.toStdString() << std::endl;
    if(this->stateName != "")
    {
    std::cout << "drawing a vertex..." << std::endl;
    std::cout << vertexMask->width() << std::endl;
    std::cout << vertexMask->height() << std::endl;
    std::cout << vertexMask->x() << std::endl;
    std::cout << vertexMask->y() << std::endl;
    QPen pen = QPen(QBrush(Qt::gray), 3);
    pen.setColor(Qt::black);
    QRectF vertexImage = QRectF(this->width()/4, this->width()/4, this->width()/2, this->height()/2);
    QFont f = QFont("Times New Roman", 2*vertexImage.height()/5);
    QPainter *paint = new QPainter(this);
    if(selected)
    {
        QPen selectPen = QPen(QBrush(Qt::black), 1);
        selectPen.setColor(Qt::black);
        selectPen.setStyle(Qt::DotLine);
        paint->setPen(selectPen);
        paint->drawRect(vertexImage);
    }
    paint->setFont(f);
    paint->setPen(pen);
    paint->setBrush(QBrush(Qt::white));
    paint->drawEllipse(vertexImage);
    paint->drawText(vertexImage.x() + vertexImage.width()/2, vertexImage.y(), stateName);
    f = QFont("Times New Roman", vertexImage.height()/2);
    paint->setFont(f);
    if(isFinal)
        paint->drawText(vertexImage.x()+1*vertexImage.width()/3, vertexImage.y()+3*vertexImage.height()/4, "#");
    paint->end();
    }
}

void automatonVertex::moveVertex(QPointF pos)
{
    this->move(pos.toPoint());
    this->vertexMask->moveTo(this->x() + this->width()/4, this->y() + this->height()/4);
}

void automatonVertex::select()
{
    selected = true;
    repaint();
    //updatePixmap();
}

void automatonVertex::unselect()
{

    selected = false;
    repaint();
    //updatePixmap();
}





