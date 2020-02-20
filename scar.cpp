#include "scar.h"

sCar::sCar()
{

}

void sCar::move()
{
    switch (direction) {
    case eDirection::UP:
        rect.pos.y -= speed;
        break;
    case eDirection::DOWN:
        rect.pos.y += speed;
        break;
    case eDirection::RIGHT:
        rect.pos.x += speed;
        break;
    case eDirection::LEFT:
        rect.pos.x -= speed;
        break;
    }
}

void sCar::moveToStart(const eDirection &direct)
{
    direction = direct;
    switch (direction) {
    case eDirection::UP:
        rect = Rectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT,
                     rect.size.width, rect.size.height);
        error_rect_1.pos.x = SCREEN_WIDTH / 2;
        error_rect_1.pos.y = SCREEN_HEIGHT / 2;
        error_rect_2.pos.x = SCREEN_WIDTH / 2;
        error_rect_2.pos.y = SCREEN_HEIGHT / 2 - rect.size.height;
        break;
    case eDirection::DOWN:
        rect = Rectangle(SCREEN_WIDTH / 2  - rect.size.width, 0,
                     rect.size.width, rect.size.height);
        error_rect_1.pos.x = SCREEN_WIDTH / 2   - rect.size.width;
        error_rect_1.pos.y = SCREEN_HEIGHT / 2  - rect.size.height;
        error_rect_2.pos.x = SCREEN_WIDTH / 2   - rect.size.width;
        error_rect_2.pos.y = SCREEN_HEIGHT / 2;
        break;
    case eDirection::RIGHT:
        rect = Rectangle(0, SCREEN_HEIGHT / 2,
                     rect.size.width, rect.size.height);
        error_rect_1.pos.x = SCREEN_WIDTH / 2   - rect.size.width;
        error_rect_1.pos.y = SCREEN_HEIGHT / 2;
        error_rect_2.pos.x = SCREEN_WIDTH / 2;
        error_rect_2.pos.y = SCREEN_HEIGHT / 2;
        break;
    case eDirection::LEFT:
        rect = Rectangle(SCREEN_WIDTH, SCREEN_HEIGHT / 2 - rect.size.height,
                     rect.size.width, rect.size.height);
        error_rect_1.pos.x = SCREEN_WIDTH / 2;
        error_rect_1.pos.y = SCREEN_HEIGHT / 2  - rect.size.height;
        error_rect_2.pos.x = SCREEN_WIDTH / 2   - rect.size.width;
        error_rect_2.pos.y = SCREEN_HEIGHT / 2  - rect.size.height;
        break;
    }
}

Rectangle sCar::futurePos()
{
    switch (direction) {
    case eDirection::UP:
        return Rectangle(rect.pos.x, rect.pos.y - speed, rect.size.width, rect.size.height);
    case eDirection::DOWN:
        return Rectangle(rect.pos.x, rect.pos.y + speed, rect.size.width, rect.size.height);
    case eDirection::RIGHT:
        return Rectangle(rect.pos.x + speed, rect.pos.y, rect.size.width, rect.size.width);
    case eDirection::LEFT:
        return Rectangle(rect.pos.x - speed, rect.pos.y, rect.size.width, rect.size.height);
    }
    return rect;
}
