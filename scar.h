#ifndef SCAR_H
#define SCAR_H

#include <QDebug>
#include <random>

#include "rectangle.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

const int car_width = 100;
const int car_height = 100;

class sCar
{
public:
    sCar();
    virtual ~sCar() {}
    Rectangle rect;
    eDirection direction;
    int speed = 10;

    Rectangle error_rect_1;
    Rectangle error_rect_2;

    int x() { return rect.pos.x; }
    int y() { return rect.pos.y; }
    int width() { return rect.size.width; }
    int height() { return rect.size.height; }

    void move();
    void moveToStart(const eDirection &direct);
    Rectangle futurePos();
    virtual int getFuel() = 0;
    virtual void refill(int count) = 0;
};

struct sGasEngine : virtual sCar {
    int getFuel() { return fuel; }
    void refill(int count) { fuel += count; }
    void move() { fuel--; sCar::move(); }
    int fuel;
};

struct sElectroCar : virtual sCar {
    int getFuel() { return charge; }
    void refill(int count) { charge += count; }
    void move() { charge--; sCar::move(); }
    int charge;
};

struct sHybrid : sGasEngine, sElectroCar {
    void refill(int count) { charge += count / 2; fuel += count / 2; }
    int getFuel() { return charge + fuel; }
    void move() {
        if (rand() % 2 == 0)
            charge--;
        else
            fuel--;
        sCar::move();
    }
};

class Carfax
{
public:
    Carfax() {
        rect_1.pos.x = SCREEN_WIDTH / 2   - rect_1.size.width;
        rect_1.pos.y = SCREEN_HEIGHT / 2  - rect_1.size.height;

        rect_2.pos.x = SCREEN_WIDTH / 2;
        rect_2.pos.y = SCREEN_HEIGHT / 2  - rect_2.size.height;

        rect_3.pos.x = SCREEN_WIDTH / 2   - rect_3.size.width;
        rect_3.pos.y = SCREEN_HEIGHT / 2;

        rect_4.pos.x = SCREEN_WIDTH / 2;
        rect_4.pos.y = SCREEN_HEIGHT / 2;

        //qDebug() << rect_4.pos.x << " " << rect_4.pos.y;
    }

    Rectangle rect_1;
    Rectangle rect_2;
    Rectangle rect_3;
    Rectangle rect_4;
};

#endif // SCAR_H


