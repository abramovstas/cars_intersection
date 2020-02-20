#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
//#include <QGraphicsItem>
//#include <QListWidgetItem>
#include <QTimer>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    scene->setSceneRect(QRectF(0, 0, 1024, 768));
    ui->graphicsView->setScene(scene);

    initScene();

    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainLoop()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete timer;
    pointersMap.clear();
    delete ui;
}

void MainWindow::initScene()
{
    addNewCar(spawnCarFromBot());
    addNewCar(spawnCarFromLeft());
    addNewCar(spawnCarFromTop());
    addNewCar(spawnCarFromRight());
}

bool MainWindow::futurePosIntersects(sCar *car, sCar *other_car)
{
    if (car != other_car && car->futurePos().intersects(other_car->futurePos()))
        return true;

    return false;
}

//  Передвижение машины
int MainWindow::moveCar(sCar *car)
{
    switch (car->direction) {                                               //  Смотрю направление движения
    case eDirection::UP:
        if (car->futurePos().intersects(carfax.rect_4) && checkBlock(car))  //  Если будущие координаты машины пересекают перекресток
                return -1;                                                  //  Проверяю не создаст ли машина пробку на перекрестке
                                                                            //  Если создаст не двигаю машину
        for (auto& car2 : pointersMap) {                                    //  Если пробки нет перебираю все машины
            if (futurePosIntersects(car, car2)) {                           //  Смотрю пересекаются ли будущие координаты моей машины и других машин
                if (car2->direction == eDirection::RIGHT &&                 //  Если пересекаются смотрю кто должен проехать
                        car->x() < car2->x() + car2->width()) {
                    return -1;
                }
                else if (car2->direction == eDirection::LEFT &&
                        car2->x() <= car->x() + car->width()) {
                    return -1;
                }
            }
        }
        break;
    case eDirection::LEFT:
        if (car->futurePos().intersects(carfax.rect_2))
            if (checkBlock(car))
                return -1;
        for (auto& car2 : pointersMap) {
            if (futurePosIntersects(car, car2)) {
                if (car2->direction == eDirection::UP &&
                        car2->y() < car->y() + car->height()) {
                    return -1;
                }
                if (car2->direction == eDirection::DOWN &&
                        car2->y() + car2->height() >= car->y() ) {
                    return -1;
//                    if (car->x() > car2->x() && car->x() - car->speed <= car2->x() + car2->width()) {
//                        return -1;
//                    }
                }
            }
        }
        break;
    case eDirection::RIGHT:
        if (car->futurePos().intersects(carfax.rect_3))
            if (checkBlock(car))
                return -1;
        for (auto& car2 : pointersMap) {
            if (futurePosIntersects(car, car2)) {
//                qDebug() << "RIGHT " << car->x() << " " << car->y() << " car2 " << car2->x() << " " << car2->y();
                if (car2->direction == eDirection::UP &&
                        car2->y() <= car->y() + car->height()) {
                    return -1;
                }
                else if (car2->direction == eDirection::DOWN &&
                        car2->y() + car2->height() > car->y()) {
                    return -1;
                }
            }
        }
        break;
    case eDirection::DOWN:
        if (car->futurePos().intersects(carfax.rect_1))
            if (checkBlock(car))
                return -1;
        for (auto& car2 : pointersMap) {
            if (futurePosIntersects(car, car2)) {
                if (car2->direction == eDirection::RIGHT &&
                        car2->x() + car2->width() >= car->x()) {
                    return -1;
                }
                if (car2->direction == eDirection::LEFT &&
                        car->x() + car->width() > car2->x()) {
//                    qDebug() << "c_DOWN " << car->x() << car->y() << " car2 LEFT " << car2->x() << " " << car2->y();
                    return -1;
                }
            }
        }
        break;
    }
    car->move();
    //qDebug()<< "CAR_DIR " << int(car->direction) << " CAR_X_Y " << car->x() << " " << car->y();
    return 1;
}

bool MainWindow::checkBlock(sCar *car)
{
    bool rect_1 = false;
    bool rect_2 = false;
    bool rect_3 = false;
    bool rect_4 = false;

    for (auto& car22 : pointersMap) {
        if (car != car22) {
            if (car22->rect.intersects(carfax.rect_1))
                rect_1 = true;
            if (car22->rect.intersects(carfax.rect_2))
                rect_2 = true;
            if (car22->rect.intersects(carfax.rect_3))
                rect_3 = true;
            if (car22->rect.intersects(carfax.rect_4))
                rect_4 = true;
        }
    }
    if (rect_1 && rect_2 && rect_3)
        return true;
    if (rect_2 && rect_3 && rect_4)
        return true;
    if (rect_3 && rect_4 && rect_1)
        return true;
    if (rect_4 && rect_1 && rect_2)
        return true;

    return false;
}

sCar* MainWindow::spawnCarType()
{
    int carType = rand() % 3;
    switch (carType) {
    case 0:
        return new sGasEngine();
    case 1:
        return new sElectroCar();
    case 2:
        return new sHybrid();
    }
    return new sGasEngine();
}

sCar* MainWindow::spawnCarFromTop()
{
    sCar* car = spawnCarType();
    car->moveToStart(eDirection::DOWN);
    return car;
}

sCar* MainWindow::spawnCarFromBot()
{
    sCar* car = spawnCarType();
    car->moveToStart(eDirection::UP);
    return car;
}

sCar* MainWindow::spawnCarFromLeft()
{
    sCar* car = spawnCarType();
    car->moveToStart(eDirection::RIGHT);
    return car;
}

sCar* MainWindow::spawnCarFromRight()
{
    sCar* car = spawnCarType();
    car->moveToStart(eDirection::LEFT);
    return car;
}

void MainWindow::moveAllCar()
{
    for (auto& car : pointersMap) {
        //  Если подвинул машину
        if (moveCar(car) > 0) {
            //  Смотрю не ушла ли она за пределы сцены
            if (car->rect.pos.x <= 0 ||
                car->rect.pos.x >= SCREEN_WIDTH ||
                car->rect.pos.y <= 0 ||
                car->rect.pos.y >= SCREEN_HEIGHT) {
                //  Если ушла, передвигаю её в начальную позицию
                car->moveToStart(car->direction);
            }
        }
    }
}

void MainWindow::updateAllCarScenePos()
{
    QMapIterator<QGraphicsItem*, sCar*> i(pointersMap);
    while (i.hasNext()) {
        i.next();
        int x = i.value()->rect.pos.x;
        int y = i.value()->rect.pos.y;
        i.key()->setPos(x, y);
    }
}

void MainWindow::mainLoop()
{
    timer->stop();
    moveAllCar();
    updateAllCarScenePos();
    //    Ломаются координаты
    if (updateSpeed) {
        foreach (auto &car, pointersMap.values()) {
            car->speed = ui->sbox_speed->value();
        }
    }
    timer->start();
}

void MainWindow::addNewCar(sCar *car)
{
    Car *g_car = nullptr;
    switch (car->direction) {
    case eDirection::UP:
        g_car = new Car(0, Qt::green);
        break;
    case eDirection::RIGHT:
        g_car = new Car(90, Qt::gray);
        break;
    case eDirection::LEFT:
        g_car = new Car(270, Qt::blue);
        break;
    case eDirection::DOWN:
        g_car = new Car(180, Qt::red);
        break;
    }
    if (g_car) {
        scene->addItem(g_car);
        g_car->setPos(QPoint(car->rect.pos.x, car->rect.pos.y));
        pointersMap.insert(g_car, car);
    }
}

void MainWindow::on_sbox_speed_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateSpeed = true;
}
