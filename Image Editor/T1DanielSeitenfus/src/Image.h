#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Bmp.h"

class Image {

    int x, y, selected;
    Bmp *bmp;

public:
    Image(Bmp *_bmp, int _x, int _y) {
        x = _x;
        y = _y;
        selected = false;
        bmp = _bmp;
    }

    void render() {
        // Desenhar a imagem dentro do retângulo

       for (int i = 0; i < bmp->getHeight(); i++) {
           for (int j = 0; j < bmp->getWidth(); j++) {
               // Obter a cor do pixel da imagem
               unsigned char r = bmp->getImage()[(i * bmp->getWidth() + j) * 3];     // Componente vermelho
               unsigned char g = bmp->getImage()[(i * bmp->getWidth() + j) * 3 + 1]; // Componente verde
               unsigned char b = bmp->getImage()[(i * bmp->getWidth() + j) * 3 + 2]; // Componente azul

               // Desenhar o pixel na tela dentro do retângulo
               CV::color(r / 255.0, g / 255.0, b / 255.0); // Normalizar e definir a cor
               CV::point(x + j, y + i);

           }
       }

        if(selected) {
             CV::color(0,0,0);
            for(int i=0; i<5; i++) {
                CV::rect(x-i,y+i,x+bmp->getWidth()+i, y+bmp->getHeight()-i);
            }
        }


       // CV::rect(x-1,y-1,x+bmp->getWidth()-1, y+bmp->getHeight()-1);
    }

    bool checkCollision(int mx, int my) {
      return mx >= x && mx <= (x + bmp->getWidth()) && my >= y && my <= (y + bmp->getHeight());

    }

    void setPosition(int _x, int _y) {
        x = _x;
        y = _y;
    }

    void setSelected(bool _selected) {
        selected = _selected;
    }

    void toggleSelected() {
        selected = !selected;
    }

    Bmp* getBmp() {
        return bmp;
    }

    bool isSelected() {
        return selected;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

};


#endif // IMAGE_H_INCLUDED
