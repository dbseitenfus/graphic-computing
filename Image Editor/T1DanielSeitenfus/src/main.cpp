/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2024
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "gl_canvas2d.h"
#include "Bmp.h"
#include "Image.h"
#include "ImageManager.h"
#include "ImagePanel.h"
#include "ImageSelectedSection.h"

using namespace std;

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1000, screenHeight = 600;

ImagePanel *imagePanel;
ImageSelectedSection *imageSelectedSection;

int mouseX, mouseY;

int imagePanelX=350, imagePanelY=40, imagePanelHeight=600, imagePanelWidth=650;


void render() {
    imagePanel->render();
    imageSelectedSection->setImageSelected(imagePanel->getSelectedImage()); //TODO: Otimizar
    imageSelectedSection->render();
    //Sleep(10);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x;
    mouseY = y;
    imagePanel->onMouseUpdated(x, y, state);
}


int main(void) {
   ios_base::sync_with_stdio(false); //aumentar a performance do print/cout

   imagePanel = new ImagePanel(imagePanelX,imagePanelY,imagePanelX+imagePanelWidth,imagePanelY+imagePanelHeight);
   imagePanel->addImage(".//T1DanielSeitenfus//images//img3.bmp");
   //imagePanel->addImage(".//T1DanielSeitenfus//images//img2.bmp");
   imagePanel->addImage(".//T1DanielSeitenfus//images//img1.bmp");
   imagePanel->addImage(".//T1DanielSeitenfus//images//img1.bmp");
   imagePanel->convertBGRtoRGB();
cout << "Cheguei";
   imageSelectedSection = new ImageSelectedSection(20, 40, 300, 550, imagePanel->getSelectedImage());

   CV::init(screenWidth, screenHeight, "Trabalho 1");
   CV::run();
}
