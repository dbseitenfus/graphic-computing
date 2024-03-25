#ifndef IMAGESELECTEDVIEW_H_INCLUDED
#define IMAGESELECTEDVIEW_H_INCLUDED

#include "gl_canvas2d.h"
#include "Image.h"

struct ImageSelected {
    int margin;
    int x1;
    int y1;
    int x2;
    int y2;
    Image *image;
};

class ImageSelectedSection {
int width, height;
int x1, y1, x2, y2;
ImageSelected imageSelected;

public:
    ImageSelectedSection(int _x, int _y, int _width, int _height, Image *_image) {
        x1 = _x;
        y1 = _y;
        width = _width;
        height = _height;
        x2 = x1+width;
        y2 = y1+height;

        setupImageSelectedView(_image);
    }

    void setupImageSelectedView(Image *_image) {
        imageSelected.image = _image;
        imageSelected.margin = 10;
        imageSelected.x1 = x1 + imageSelected.margin;
        imageSelected.y1 = y2 - 250;
        imageSelected.x2 = x2 - imageSelected.margin;
        imageSelected.y2 = y2 - imageSelected.margin;

        if(_image != nullptr) {
            imageSelected.image = new Image(_image->getBmp(), x1, y1);
            imageSelected.image->setSelected(true);
            imageSelected.image->setPosition(x1, y1);
        }
    }

    void setupButtons() {

    }

    void render() {
       CV::color(0,0,0);
       CV::rect(x1,y1,x2,y2);
       CV::rect(imageSelected.x1, imageSelected.y1, imageSelected.x2, imageSelected.y2);
       if(imageSelected.image != nullptr) imageSelected.image->render();
    }

    void setImageSelected(Image *_image) {
        if(_image != nullptr) {
            imageSelected.image = new Image(_image->getBmp(), x1, y1);
            imageSelected.image->setSelected(true);
            imageSelected.image->setPosition(imageSelected.x1, imageSelected.y1);
        }
    }

};

#endif // IMAGESELECTEDVIEW_H_INCLUDED
