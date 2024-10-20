//Yash
#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H

#include "StandardIncludes.h"

struct Color
{
    byte R;
    byte G;
    byte B;
    byte A;

    Color()
        : R(255), G(255), B(255), A(255) {}

    Color(byte _r, byte _g, byte _b, byte _a = 255)
        : R(_r), G(_g), B(_b), A(_a) {}
};

struct Point
{
    float X;
    float Y;

    Point(float x = 0.0f, float y = 0.0f)
        : X(x), Y(y)
    {}
};


struct Rect
{
    int X1;
    int Y1;
    int X2;
    int Y2;

    Rect()
        : X1(0), Y1(0), X2(0), Y2(0) {}

    Rect(int _x1, int _y1, int _x2, int _y2)
        : X1(_x1), Y1(_y1), X2(_x2), Y2(_y2) {}

    int Width() const { return X2 - X1; }
    int Height() const { return Y2 - Y1; }
};

#endif // BASIC_STRUCTS_H
