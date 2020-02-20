#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "scar.h"
#include "car.h"

class DiagramScene;
class sCar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mainLoop();

    void on_sbox_speed_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QTimer *timer;
    QMap<QGraphicsItem*, sCar*> pointersMap;

    void addNewCar(sCar *car);

    void initScene();
    sCar* spawnCarType();
    sCar* spawnCarFromTop();
    sCar* spawnCarFromBot();
    sCar* spawnCarFromLeft();
    sCar* spawnCarFromRight();
    void moveAllCar();
    void updateAllCarScenePos();
    int moveCar(sCar *car);
    bool checkBlock(sCar *car);
    bool futurePosIntersects(sCar *car, sCar *other_car);

    Carfax carfax;

    bool updateSpeed = false;
};

#endif // MAINWINDOW_H
