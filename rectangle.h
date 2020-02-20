#ifndef RECTANGLE_H
#define RECTANGLE_H

enum class eDirection : int {
    UP,
    LEFT,
    RIGHT,
    DOWN
};

struct sPos {
    sPos() { x = 0; y = 0; }
    sPos(int aX, int aY) { x = aX; y = aY; }
    int x;
    int y;
};

struct sSize
{
    sSize() { width = 100; height = 100; }
    sSize(int aW, int aH) { width = aW; height = aH; }
    int width;
    int height;
};

class Rectangle
{
public:
    Rectangle() {}
    Rectangle(int x, int y, int w, int h) { pos.x = x; pos.y = y; size.width = w; size.height = h; }
    sPos pos;
    sSize size;
    bool intersects(const Rectangle& other) {
        bool b1 = other.pos.x + other.size.width <= pos.x;
        bool b2 = other.pos.y + other.size.height <= pos.y;
        bool b3 = other.pos.x >= pos.x + size.width;
        bool b4 = other.pos.y >= pos.y + size.height;
        bool result = !(b1 || b2 || b3 || b4);
        return result;
    }
};

#endif // RECTANGLE_H
