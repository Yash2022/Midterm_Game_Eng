//Ramanooj
#include <SDL_stdinc.h>
#ifndef MYCOLOR_H
#define MYCOLOR_H
    
struct MyColor
{
    Uint8 R;
    Uint8 G;
    Uint8 B;
    Uint8 A;

    MyColor(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
        : R(r), G(g), B(b), A(a)
    {}
};

#endif // MYCOLOR_H
