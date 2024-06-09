#ifndef POINTER_H_INCLUDED
#define POINTER_H_INCLUDED

#include "Vector2.h"

class Pointer {

public:

    //Pointer
    float angle = 1;
    float r = 50;
    Vector2 pointer;
    Vector2 origin;

    Pointer() {
        origin.x = 0;
        origin.y = 0;
    }

    void render() {
        CV::translate(screenWidth/2, screenHeight/2);
        pointer.x = r*cos(angle);
        pointer.y = r*sin(angle);
        CV::color(0,0,0);
        CV::line(origin, pointer);
        angle -= 0.001;
    }

};


#endif // POINTER_H_INCLUDED
