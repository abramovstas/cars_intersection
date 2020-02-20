#ifndef CAR_H
#define CAR_H

#include <QGraphicsObject>
#include <QBrush>

class Car : public QGraphicsObject
{
    Q_OBJECT
public:
    Car(qreal angle = 0, QColor color = Qt::green);
    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    QBrush color;
};

#endif // CAR_H
