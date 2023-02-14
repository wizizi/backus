#ifndef AUTOMATONVERTEX_H
#define AUTOMATONVERTEX_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QDrag>
#include <QMimeData>

namespace Ui {
class automatonVertex;
}

class automatonVertex : public QLabel
{
    Q_OBJECT

public:
    explicit automatonVertex(QWidget *parent = nullptr);
    explicit automatonVertex(QWidget *parent, int size, QString sN, bool isF);
    void moveVertex(QPointF pos);
    void updatePixmap();
    QString stateName = "";
    bool isFinal = true;
    bool placed = false;
    void select();
    void unselect();
    QRectF *vertexMask;
    ~automatonVertex();

private:
    Ui::automatonVertex *ui;
    bool selected = false;
    void paintEvent(QPaintEvent *event);

};

#endif // AUTOMATONVERTEX_H
