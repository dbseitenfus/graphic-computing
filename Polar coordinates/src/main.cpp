
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Pointer.h"
#include "Circle.h"
#include "Spiral.h"
#include "RotaryHacksaw.h"
#include <vector>

using namespace std;

int screenWidth = 750, screenHeight = 750;

Pointer *pointer;
Circle *circle;

Spiral spiral;
RotaryHacksaw rotaryHacksaw;
Vector2 in[4];
Vector2 out[4];

Vector2 translate(Vector2 point, float value) {
    point.x += value;
    point.y += value;
    return point;
}

Vector2 scale(Vector2 point, float value) {
    point.x *= value;
    point.y *= value;
    return point;
}

Vector2 reflect(Vector2 point) {
    point.x *= -1;
    return point;
}

Vector2 rotate(Vector2 point, float angle) {
    int x = point.x;
    int y = point.y;

    point.x = x*cos(angle) - y*sin(angle);
    point.y = x*sin(angle) + y*cos(angle);
    return point;
}

void draw(Vector2 out[4]) {
    for(int i=0; i<4; i++) {
        Vector2 p0 = out[i];
        Vector2 p1 = out[(i+1)%4];
        CV::line(p0, p1);
    }
}

void renderSquare() {
    CV::color(0,0,0);
    for(int i=0; i<4; i++) {
        //out[i] = in[i];
        //out[i] = scale(in[i],2);

        out[i] = rotate(in[i], 1);

        //out[i] = translate(out[i], 100);
    }

    draw(out);

    CV::color(0,0,1);
    for(int i=0; i<4; i++) {
        out[i] = rotate(in[i], 2);
        out[i] = translate(out[i], 300);
    }

    draw(out);

    CV::color(0,1,0);
    for(int i=0; i<4; i++) {
        out[i] = rotate(in[i], 3);
        out[i] = translate(out[i], 300);

    }

    draw(out);
}

void drawCartesianAxis() {
    CV::color(1,0,0);
    CV::line(0,0, 0, screenHeight-300);
    CV::line(0,0, screenWidth-300, 0);
}


void render() {
    CV::translate(screenWidth/2-200, screenHeight/2-200);
    renderSquare();
    drawCartesianAxis();

    //pointer->render();
    //circle->render();
    //spiral.render();
    //rotaryHacksaw.render();
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {

}


int main(void) {
    int squareSize = 50;
    Vector2 p0, p1, p2, p3;
    p0.set(0,0);
    p1.set(0, squareSize);
    p2.set(squareSize,squareSize);
    p3.set(squareSize, 0);
    in[0] = p0;
    in[1] = p1;
    in[2] = p2;
    in[3] = p3;
    pointer = new Pointer();
    circle = new Circle();
   CV::init(screenWidth, screenHeight, "T3 - Daniel Seitenfus");
   CV::run();
}
