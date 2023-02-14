#ifndef AUTOMATONFIELD_H
#define AUTOMATONFIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLayout>
#include "automaton.h"
#include "automatonvertex.h"
#include "addconnwindow.h"

struct edgeMask
{
    edgeMask();
    ~edgeMask();
    edgeMask(QRectF m, QString ini, QString symb, QString res);
    edgeMask& operator=(const edgeMask &S);
    bool operator==(const edgeMask &S) const;
    QRectF mask;
    QString iniState;
    QString symbol;
    QString resState;
};

namespace Ui {
class automatonField;
}

class automatonField : public QWidget
{
    Q_OBJECT

public:
    explicit automatonField(QWidget *parent = nullptr);
    void addState(QPoint pos, QString name, bool isFinal);
    void changeState(QString oldName, QString newName, bool newFin);
    void clearVertices();
    void updateVertices();
    void deleteVertex(QString S);
    ~automatonField();
    Automaton * A;

private:
    Ui::automatonField *ui;
    QPointF vertexDragStart;
    QPointF vertexRelPos;
    QPointF trackedCursorPos;
    bool connectingInProgress = false;
    bool draggingInProgress = false;
    bool shiftFlag = false;
    QVector<automatonVertex *> vertices;
    QVector<automatonVertex *> selectVertices = {};
    QVector<edgeMask> edges = {};
    QVector<edgeMask> selectEdges = {};
    automatonVertex * draggedVertex;
    Qt::DropAction dropAction;
    void placeEdges(QPainter * painter);
    void vertexPlacement(int vn, int x, int y);
    void createVertex(QPoint pos, QString name, bool isFinal);
    void openChangeStateWindow(QString name, bool fin);
    void openAddStateWindow(QPoint pos);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // AUTOMATONFIELD_H
