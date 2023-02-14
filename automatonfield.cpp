#include "automatonfield.h"
#include "ui_automatonfield.h"
#include <QPainterPath>
#include <iostream>


edgeMask::edgeMask()
{

}
edgeMask::~edgeMask()
{

}
edgeMask::edgeMask(QRectF m, QString ini, QString symb, QString res)
{
    mask = m;
    iniState = ini;
    symbol = symb;
    resState = res;
}

edgeMask& edgeMask::operator=(const edgeMask &S)
{
    mask = S.mask;
    iniState = S.iniState;
    symbol = S.symbol;
    resState = S.resState;
    return *this;
}

bool edgeMask::operator==(const edgeMask &S) const
{
    return iniState == S.iniState && symbol == S.symbol && resState == S.resState;
}

automatonField::automatonField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::automatonField)
{
    setFocusPolicy(Qt::ClickFocus);
    setAcceptDrops(true);
    draggedVertex = nullptr;
    this->A = nullptr;
    ui->setupUi(this);
    A = new Automaton();
}

automatonField::~automatonField()
{
    delete ui;
}

void automatonField::addState(QPoint pos, QString name, bool isFinal)
{
    A->addState(name);
    A->setFinality(name, isFinal);
    createVertex(pos, name, isFinal);
}

void automatonField::changeState(QString oldName, QString newName, bool newFin)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->stateName == oldName)
        {
            vertices[i]->stateName = newName;
            vertices[i]->isFinal = newFin;
            vertices[i]->repaint();
            vertices[i]->updatePixmap();
        }
    }
    A->setFinality(oldName, newFin);
    A->changeName(oldName, newName);
}

void automatonField::createVertex(QPoint pos, QString name, bool isFinal)
{
    std::cout << "Creating a vertex..." << std::endl;
    vertices.append(new automatonVertex(this, 64, name, isFinal));
    std::cout << vertices.last()->stateName.toStdString() << std::endl;
    vertices.last()->moveVertex(pos);
    vertices.last()->show();

}

void automatonField::clearVertices()
{
    for(int i = 0; i < vertices.size(); i++)
        vertices[i]->close();
    vertices.clear();
}

void automatonField::updateVertices()
{
    clearVertices();
    std::cout << "vertices left: " << vertices.size() << std::endl;
    std::cout << "vertices needed: " << A->getInAlphabet().length() << std::endl;
    for(int i = 0; i < A->getInAlphabet().length(); i++)
    {
        std::cout << "placing vertex" << A->getInAlphabet()[i].name.toStdString() << std::endl;
        createVertex(QPoint(0, i*32), A->getInAlphabet()[i].name, A->getInAlphabet()[i].isFinal);
    }
    std::cout << "new vertices created:" << vertices.size() << std::endl;
    if(vertices.size() > 0)
        vertexPlacement(0, 40, height()/2-10);

}


void automatonField::vertexPlacement(int vn, int x, int y)
{
    std::cout << "about to place vertex..." << std::endl;
    vertices[vn]->moveVertex(QPoint(x, y));
    vertices[vn]->placed = true;
    std::cout << "vertex placed!" << std::endl;
    int yshift = 0;
    int yshiftStep = 80;
    int fling = 0;
    for(int i = 0; i < A->getInAlphabet().size(); i++)
    {
       if (!A->getConnections().get(vn, i).isEmpty() && vn != i && !vertices[i]->placed)
       {
           if(fling%2 == 0)
           {
               yshift *= -1;
               yshiftStep *= -1;
           }
           else
           {
               yshift += yshiftStep;
           }
           vertexPlacement(i, x+100, y + yshift);
           fling++;
       }
    }
}



void drawArrowHead(QPainter *painter, qreal x, qreal y, qreal cx, qreal cy)
{
    QLineF myLine = QLineF(cx, cy, x, y);
    painter->setBrush(QBrush(Qt::black));
      qreal arrowSize = 12;
      QPointF arrowP1 = QPointF(x - sin(myLine.angle()*M_PI/180 + M_PI /3) * arrowSize,
        y - cos(myLine.angle()*M_PI/180 + M_PI / 3) * arrowSize);
      QPointF arrowP2 = QPointF(x - sin(myLine.angle()*M_PI/180 + M_PI - M_PI / 3) * arrowSize,
      y - cos(myLine.angle()*M_PI/180 + M_PI - M_PI / 3) * arrowSize);
      painter->drawPolygon({arrowP1, arrowP2, myLine.p2()});
    painter->setBrush(QBrush());
}

void automatonField::placeEdges(QPainter * painter)
{
    edges.clear();
    painter->setBrush(QBrush());
    int divergence = 0;
    float divx = 0;
    float divy = 0;
    int fling = 0;
    int xs, ys, xd, yd;
    QPainterPath edgeDrawer;
    for(int i = 0; i < A->getInAlphabet().size(); i++)
    {
       int vsize = vertices[i]->vertexMask->height();
       for(int j = i; j < A->getInAlphabet().size(); j++)
       {
            if (i != j)
            {
                divergence = 0;
                divx = 0;
                divy = 0;
                for(int k = 0; k < vertices.size(); k++)
                    fling = vertices[k]->vertexMask->intersects(QRectF(vertices[i]->vertexMask->center(), vertices[j]->vertexMask->center()))
                            && vertices[k] != vertices[i] && vertices[k] != vertices[j];
                //fling = abs(vertices[i]->vertexMask->x() - vertices[j]->vertexMask->x()) > 100;
                QLineF guidingLine = QLineF(vertices[i]->vertexMask->center(), vertices[j]->vertexMask->center());
                qreal alpha = M_PI * QLineF(vertices[i]->vertexMask->center(), vertices[j]->vertexMask->center()).angle()/180;
                qreal beta = M_PI * (90 - QLineF(vertices[i]->vertexMask->center(), vertices[j]->vertexMask->center()).angle())/180;
                qreal vix = vertices[i]->vertexMask->center().x();
                qreal viy = vertices[i]->vertexMask->center().y();
                qreal vjx = vertices[j]->vertexMask->center().x();
                qreal vjy = vertices[j]->vertexMask->center().y();
                QPointF spoint = QPointF(vix + vsize/2 * cos(alpha), viy - vsize/2 * sin(alpha));
                QPointF dpoint = QPointF(vjx - vsize/2 * sin(beta), vjy + vsize/2 * cos(beta));
                xs = draggedVertex == vertices[i] && draggingInProgress ? trackedCursorPos.x() : spoint.x();
                ys = draggedVertex == vertices[i] && draggingInProgress ? trackedCursorPos.y() : spoint.y();
                xd = draggedVertex == vertices[j] && draggingInProgress ? trackedCursorPos.x() : dpoint.x();
                yd = draggedVertex == vertices[j] && draggingInProgress ? trackedCursorPos.y() : dpoint.y();
                for(int k = 0; k < A->getConnections().get(i, j).size(); k++)
                {
                    if(fling % 2 == 0)
                    {
                        divx *= -1;
                        divy *= -1;
                    }
                    else
                    {
                        divergence += 30;
                        divx = yd != ys ? -(sqrt(pow(xd - xs, 2) + pow(yd - ys, 2))*tan(divergence*M_PI/180))/(2 * sqrt(1 + ((pow(xd-xs, 2))/(pow(yd-ys, 2))))) : 0;
                        divy = yd != ys ? -divx * (xd-xs)/(yd-ys) : -tan(divergence* M_PI/180)*(xd-xs)/2;
                    }
                    fling++;
                    edgeDrawer.moveTo(xs, ys);
                    edgeDrawer.quadTo(divx + (xd+xs)/2, divy + (yd+ys)/2, xd, yd);
                    painter->drawPath(edgeDrawer);
                    QPointF divpoint = QPointF(divx + (xd+xs)/2, divy + (yd+ys)/2);
                    QPointF tippoint = vertices[j]->geometry().intersected(QRectF(divpoint, vertices[j]->vertexMask->center()).toRect()).center();
                    drawArrowHead(painter, xd,
                                  yd,
                                  divx + (xd+xs)/2, divy + (yd+ys)/2);
                    //painter->drawPolyline(QPolygonF(QVector<QPointF>({QPointF(xs, ys), QPointF(divx + (xd+xs)/2, divy + (yd+ys)/2), QPointF(xd, yd)})));
                    QRectF newMask = QRectF(divx/2 + (xd+xs)/2 - 3, divy/2 + (yd+ys)/2 - 12, 12, 16);
                    edgeMask newEdge = edgeMask(newMask, vertices[i]->stateName, A->getConnections().get(i, j)[k], vertices[j]->stateName);
                    edges.append(newEdge);
                    painter->drawText(divx/2 + (xd+xs)/2 - 2, divy/2 + (yd+ys)/2, A->getConnections().get(i, j)[k]);
                }
                for(int k = 0; k < A->getConnections().get(j, i).size(); k++)
                {
                    if(fling % 2 == 0)
                    {
                        divx *= -1;
                        divy *= -1;
                    }
                    else
                    {
                        divergence += 30;
                        divx = yd != ys ? -(sqrt(pow(xd - xs, 2) + pow(yd - ys, 2))*tan(divergence*M_PI/180))/(2 * sqrt(1 + ((pow(xd-xs, 2))/(pow(yd-ys, 2))))) : 0;
                        divy = yd != ys ? -divx * (xd-xs)/(yd-ys) : -tan(divergence*M_PI/180)*(xd-xs)/2;
                    }
                    fling++;
                    edgeDrawer.moveTo(xs, ys);
                    edgeDrawer.quadTo(divx + (xd+xs)/2, divy + (yd+ys)/2, xd, yd);
                    painter->drawPath(edgeDrawer);
                    QPointF divpoint = QPointF(divx + (xd+xs)/2, divy + (yd+ys)/2);
                    QPointF tippoint = vertices[i]->geometry().intersected(QRectF(divpoint, vertices[i]->vertexMask->center()).toRect()).center();
                    drawArrowHead(painter, xs,
                                  ys,
                                  divx + (xd+xs)/2, divy + (yd+ys)/2);
                    QRectF newMask = QRectF(divx/2 + (xd+xs)/2 - 3, divy/2 + (yd+ys)/2 - 12, 12, 16);
                    edgeMask newEdge = edgeMask(newMask, vertices[j]->stateName, A->getConnections().get(j, i)[k], vertices[i]->stateName);
                    edges.append(newEdge);
                    //painter->drawPolyline(QPolygonF(QVector<QPointF>({QPointF(xs, ys), QPointF(divx + (xd+xs)/2, divy + (yd+ys)/2), QPointF(xd, yd)})));
                    painter->drawText(divx/2 + (xd+xs)/2 - 2, divy/2 + (yd+ys)/2 - 2, A->getConnections().get(j, i)[k]);
                }
            }
            else if(!A->getConnections().get(i, j).isEmpty())
            {
                qreal vix = draggedVertex == vertices[i] && draggingInProgress ? QPointF(trackedCursorPos - vertexRelPos).x() + vsize/2 : vertices[i]->vertexMask->x();
                qreal viy = draggedVertex == vertices[i] && draggingInProgress ? QPointF(trackedCursorPos - vertexRelPos).y() + vsize/2 : vertices[i]->vertexMask->y();
                painter->drawArc(vix, viy-vertices[i]->vertexMask->width()*1.5,
                               vertices[i]->vertexMask->width(), vertices[i]->vertexMask->width()*2, -45*16, 270*16);
                QString label = "";
                for(int k = 0; k < A->getConnections().get(i, j).size(); k++)
                {
                    label+= k == 0 ? A->getConnections().get(i, j)[k] : "," + A->getConnections().get(i, j)[k];
                    QRectF newMask = QRectF(vix-3, viy - vertices[i]->vertexMask->height()*1.5 - 12, 12, 16);
                    edgeMask newEdge = edgeMask(newMask, vertices[i]->stateName, A->getConnections().get(i, j)[k], vertices[j]->stateName);
                    edges.append(newEdge);
                }

                painter->drawText(vix, viy - vertices[i]->vertexMask->height()*1.5, label);
                drawArrowHead(painter, vix+vsize/2+5*sqrt(2)/2, viy+vsize/2-5*sqrt(2)/2, vix+vsize/2+5*sqrt(2)/2 + vsize/2, viy+vsize/2-5*sqrt(2)/2 - vsize/2);
            }
       }
    }
    QPen oldPen = painter->pen();
    QPen selPen = QPen(QBrush(Qt::gray), 1);
    selPen.setColor(Qt::black);
    selPen.setStyle(Qt::DotLine);
    painter->setPen(selPen);
    for(int i = 0; i < selectEdges.size(); i++)
        painter->drawRect(selectEdges[i].mask);
    painter->setPen(oldPen);
}



void automatonField::paintEvent(QPaintEvent *event)
{
    QPainter *paint = new QPainter(this);
    paint->setBrush(QBrush(QColor(248, 248, 248)));
    paint->setPen(QColorConstants::Transparent);
    paint->drawRect(0, 0, this->width(), this->height());
    if(A != nullptr && A->getInAlphabet().size() > 0)
    {
        //QVector<QRect> verts = QVector<QRect>(A->inAlphabet.size());
        QVector<QPolygon> edges = QVector<QPolygon>();
        QPen pen = QPen(QBrush(Qt::gray), 2);
        pen.setColor(Qt::black);
        paint->setPen(pen);
        paint->setBackground(QBrush(Qt::white));
        QFont f = QFont("Times New Roman", 12);
        paint->setFont(f);
        if(connectingInProgress)
        {
            if(draggedVertex->vertexMask->contains(trackedCursorPos))
                paint->drawArc(draggedVertex->vertexMask->x(), draggedVertex->vertexMask->y()-draggedVertex->vertexMask->width()*1.5,
                               draggedVertex->vertexMask->width(), draggedVertex->vertexMask->width()*2, -45*16, 270*16);
            else
            {
                QLineF connLine = QLineF(draggedVertex->vertexMask->center(), trackedCursorPos);
                for(int i = 0; i < vertices.size(); i++)
                {
                    if(vertices[i]->vertexMask->contains(trackedCursorPos))
                    {
                        connLine = QLine(draggedVertex->vertexMask->center().toPoint(), vertices[i]->vertexMask->center().toPoint());
                        break;
                    }
                }
                paint->drawLine(connLine);
            }
        }
        placeEdges(paint);
    }
    paint->end();

}

void automatonField::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        std::cout << vertices.size() << std::endl;
        if(!shiftFlag)
        {
            for(int i = 0; i < selectVertices.size(); i++)
                selectVertices[i]->unselect();
            selectVertices.clear();
            selectEdges.clear();
            repaint();
        }
        for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i]->vertexMask->contains(event->position()))
            {
                draggedVertex = vertices[i];
                if(!selectVertices.contains(vertices[i]))
                {
                    selectVertices.append(vertices[i]);
                    vertices[i]->select();
                }
                else if(shiftFlag)
                {
                    selectVertices.removeAt(selectVertices.indexOf(vertices[i]));
                    vertices[i]->unselect();
                }
                vertexDragStart = event->pos();
                std::cout << "Drag started..." << std::endl;
                return;
            }
            else
            {
                std::cout << "No vertices there..." << std::endl;
                if(!shiftFlag)
                {
                    for(int i = 0; i < selectVertices.size(); i++)
                        selectVertices[i]->unselect();
                    selectVertices.clear();
                }
                draggedVertex = nullptr;
            }
        }
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].mask.contains(event->position()))
            {
                if(!selectEdges.contains(edges[i]))
                {
                    selectEdges.append(edges[i]);
                    repaint();
                }
                else if(shiftFlag)
                {
                    selectEdges.removeAt(selectEdges.indexOf(edges[i]));
                    repaint();
                }
            }
        }

    }
}

void automatonField::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->pos() - vertexDragStart).manhattanLength()
            < QApplication::startDragDistance() || draggedVertex == nullptr)
            return;
    if ((event->buttons() & Qt::LeftButton))
    {
        draggingInProgress = true;
        draggedVertex->setVisible(false);
        QDrag *drag = new QDrag(this);
        drag->setPixmap(draggedVertex->pixmap());
        drag->setMimeData(new QMimeData());
        vertexRelPos = QPoint(event->pos() - draggedVertex->pos());
        drag->setHotSpot(vertexRelPos.toPoint());
        dropAction = drag->exec(Qt::MoveAction);
    }
    else if ((event->buttons() & Qt::RightButton))
    {
        connectingInProgress = true;
        QDrag *drag = new QDrag(this);
        drag->setMimeData(new QMimeData());
        dropAction = drag->exec(Qt::LinkAction);
    }

}

void automatonField::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
        draggedVertex->setVisible(false);
    event->acceptProposedAction();
    draggingInProgress = event->dropAction() == Qt::MoveAction;
    connectingInProgress = event->dropAction() == Qt::LinkAction;
}

void automatonField::dragMoveEvent(QDragMoveEvent *event)
{
    trackedCursorPos = event->position();
    this->repaint();

}

void automatonField::dragLeaveEvent(QDragLeaveEvent *event)
{
     draggedVertex->setVisible(true);
     draggingInProgress = false;
     connectingInProgress = false;
     repaint();
}


void automatonField::dropEvent(QDropEvent *event)
{
    if(event->dropAction() == Qt::MoveAction)
    {
        draggingInProgress = false;
        draggedVertex->moveVertex(QPointF(event->position() - vertexRelPos));
        std::cout << "Drag ended..." << std::endl;
        draggedVertex->setVisible(true);
        draggedVertex->repaint();
        draggedVertex = nullptr;
        this->repaint();
        event->acceptProposedAction();
    }
    else if (event->dropAction() == Qt::LinkAction)
    {
        for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i]->vertexMask->contains(event->position()))
            {
                addConnWindow d = addConnWindow(this, A, draggedVertex->stateName, vertices[i]->stateName);
                d.exec();
                event->acceptProposedAction();
                connectingInProgress = false;
                this->repaint();
                return;
            }
        }
        connectingInProgress = false;
        this->repaint();
    }

}

void automatonField::keyPressEvent(QKeyEvent *event)
{
    shiftFlag = event->key() == Qt::Key_Shift;
    if(event->key() == Qt::Key_Delete)
    {
        for(int i = 0; i < selectEdges.size(); i++)
        {
            A->deleteConn(selectEdges[i].iniState, selectEdges[i].symbol, selectEdges[i].resState);
            edges.removeAt(edges.indexOf(selectEdges[i]));
        }
        for(int i = 0; i < selectVertices.size(); i++)
        {
            A->deleteState(selectVertices[i]->stateName);
            vertices.removeAt(vertices.indexOf(selectVertices[i]));
            selectVertices[i]->close();
        }
        selectVertices.clear();
        selectEdges.clear();
        repaint();
    }
    if(shiftFlag)
        std::cout<<"Shift pressed"<<std::endl;

}

void automatonField::keyReleaseEvent(QKeyEvent *event)
{

    shiftFlag = shiftFlag && (event->key() != Qt::Key_Shift);
    if(!shiftFlag)
        std::cout<<"Shift released"<<std::endl;

}

void automatonField::mouseDoubleClickEvent(QMouseEvent *event)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->vertexMask->contains(event->pos()))
        {
            openChangeStateWindow(vertices[i]->stateName, vertices[i]->isFinal);
            return;
        }
    }
    openAddStateWindow(event->pos());

}
