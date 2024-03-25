#ifndef IMAGEPANEL_H_INCLUDED
#define IMAGEPANEL_H_INCLUDED

#include "gl_canvas2d.h"
#include "ImageManager.h"
#include "Bmp.h"
#include "Image.h"

/*
    O objetivo principal dessa classe � renderizar graficante um painel para as imagens estarem inserida.
    Features:
        - Renderizar um painel de imagens
        - Renderizar e gerenciar imagens dentro do painel, como clique, sele��o e drag and drop
        - Controlar a exibi��o das imagens, n�o permitindo que elas ultrapassem o tamanho do painel, desde a cria��o at� manipula��o
    Motiva��es:
        - Abstrair l�gicas de outras classes, tornando o c�digo mais organizado e simples de ler
*/

class ImagePanel {

int x, y, height, width;
ImageManager *imageManager;

public:

    ImagePanel(int _x, int _y, int _height, int _width) {
        x = _x;
        y = _y;
        height = _height;
        width = _width;
        imageManager = new ImageManager();
    }

    void render() {
        CV::color(0,0,0);
        CV::rect(x,y,x+width,y+height);
        imageManager->render();
    }

    void addImage(const char *fileName) {
        int imageX = x+100;
        int imageY = y+100;
        imageManager->addImage(new Image(new Bmp(fileName), imageX, imageY));
    }

    void convertBGRtoRGB() {
        imageManager->convertBGRtoRGB();
    }

    void onMouseUpdated(int mx, int my, int state) {
        if(isMouseInsidePanel(mx, my)) imageManager->onMouseUpdated(mx, my, state);
    }

    bool isMouseInsidePanel(int mx, int my) {
        return mx >= x && mx <= (x + width) && my >= y && my <= (y + height);
    }


};


#endif // IMAGEPANEL_H_INCLUDED
