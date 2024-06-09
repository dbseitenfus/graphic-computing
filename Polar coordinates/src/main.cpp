
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include "gl_canvas2d.h"

using namespace std;

int screenWidth = 750, screenHeight = 750;


void render() {

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
   CV::init(screenWidth, screenHeight, "T3 - Daniel Seitenfus");
   CV::run();
}
