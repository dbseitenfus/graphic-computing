#ifndef ROTARYHACKSAW_H_INCLUDED
#define ROTARYHACKSAW_H_INCLUDED

#include "Vector2.h"

class RotaryHacksaw {

public:

    float amplitude = 100;
    float tamanhoDaOnda = 50;
    int numeroDeOndas = 20;

    void render() {
        CV::color(0,0,0);
        for(int i=0; i<numeroDeOndas; i++) {
            float x1 = i * tamanhoDaOnda;
            float y1 =  amplitude / 2;
            float x2 = x1 + tamanhoDaOnda / 2;
            float y2 =  amplitude / 2;
            float x3 = x1 + tamanhoDaOnda;
            float y3 =  amplitude / 2;

            CV::line(x1, y1, x2, y2);
            CV::line(x2, y2, x3, y3);
        }
    }

};


#endif // ROTARYHACKSAW_H_INCLUDED
