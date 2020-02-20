#ifndef HIGHROAD_H
#define HIGHROAD_H

#include <QObject>
#include <QGraphicsObject>
#include <rectangle.h>

class Grass : public Rectangle
{
public:
    Grass(int x, int y, int w, int h) { pos.x = x; pos.y = y; size.width = w; size.height = h; }
};

class Road : public Rectangle
{
public:
    eDirection direction;
    Road() {}
    Road(int x, int y, int w, int h) { pos.x = x; pos.y = y; size.width = w; size.height = h; }
};

class HighRoad : public QObject
{
    Q_OBJECT
public:
    explicit HighRoad(QObject *parent = nullptr);

    Road r1;
    Road r2;

public slots:

};

#endif // HIGHROAD_H
