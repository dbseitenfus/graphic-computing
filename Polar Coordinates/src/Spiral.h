#ifndef SPIRAL_H_INCLUDED
#define SPIRAL_H_INCLUDED

#include "Vector2.h"

class Spiral {

public:

    int numLaps = 10;
    float moveAngle = 0;

    Spiral() {

    }

    void render() {

        float radius = 0;
        CV::color(0,0,0);
        int x = radius*cos(0);
        int y = radius*sin(0);
        for(float i=0; i<2*PI*numLaps; i+=0.1) {
            int x1 = radius*cos(i + moveAngle);
            int y1 = radius*sin(i + moveAngle);
            CV::line(x,y, x1, y1);
            x = x1;
            y = y1;
            radius += 0.1;

        }

        moveAngle += 0.005;

    }


};


#endif // SPIRAL_H_INCLUDED
