/**
* Trabalho 1 - Editor de Imagens - Computa��o Gr�fica
*  Autor: Daniel Brenner Seitenfus
*         04/2024
*
* Features:
*   - Exibi��o de Bitmaps (24 bits) de qualquer resolu��o;
*   - Drag and drop de imagens dentro do painel;
*   - Altera��o das cores da imagem, inclusive podendo combinar entre uma ou mais;
*   - Rota��o (invers�o) da imagem horizontal e verticalmente;
*   - Histograma dos canais R, G, B e Lumin�ncia, com dois estilos de visualiza��o, alterado em tempo real;
*   - Altera��o de brilho (escurer e clarear) da imagem por meio de um slider.
*   - Bot�es com �cones com fundo removido.
*
*  Instru��es:
*    - O programa possui suporte para carregar N imagens. Por padr�o, ele exibe 3, chamadas "a.bmp", "b.bmp" e "c.bmp". Para alterar as imagens, basta seguir esse padr�o no diret�rio ./Imagens.
*	 - Para alterar as cores de uma imagem selecionada, clique nos bot�es R (vermelho), G (verde), B (azul) e L (escala de cinza).
*       Os bot�es R, G e B podem ser combinados.
*    - A cores da imagem tamb�m podem ser alteradas pressionando as teclas R, G, B e L do teclado.
*    - Para alterar o brilho da imagem, deslize o bot�o do slider para esquerda, para escurecer; para direita, para clarear.
*    - O histograma exibe os canais de cores de acordo com a sele��o. Por default, R,G e B v�m selecionados.
*    - Para exibir o histograma de lumin�ncia da imagem basta clicar no bot�o L.
*    - O histograma possui dos modos de visualiza��o, com os gr�ficos preenchidos ou "vazados". Isso pode ser alterado no bot�o "Preenchido" abaixo do histograma.
*/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "gl_canvas2d.h"
#include "ImagePanel.h"
#include "ImageSelectedSection.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1100, screenHeight = 700;

ImagePanel *imagePanel;
ImageSelectedSection *imageSelectedSection;
int imagePanelX=350, imagePanelY=40, imagePanelHeight=600, imagePanelWidth=650;

/**
 * Fun��o principal para renderizar o conte�do do programa.
 */
void render() {
    imagePanel->render();
    imageSelectedSection->setImageSelected(imagePanel->getSelectedImage());
    imageSelectedSection->render();
}

/**
 * Fun��o chamada quando uma tecla � pressionada.
 * @param key C�digo da tecla pressionada.
 */
void keyboard(int key) {
    imageSelectedSection->onKeyboardUpdated(key);
}

/**
 * Fun��o chamada quando uma tecla � liberada.
 * @param key C�digo da tecla liberada.
 */
void keyboardUp(int key) {

}

/**
 * Fun��o para tratar eventos do mouse: cliques, movimentos e rolagem.
 * @param button Bot�o do mouse pressionado.
 * @param state Estado de clique do mouse.
 * @param wheel Informa��o sobre rolagem.
 * @param direction Dire��o da roda do mouse.
 * @param x Coordenada x do mouse.
 * @param y Coordenada y do mouse.
 */
void mouse(int button, int state, int wheel, int direction, int x, int y) {
    imagePanel->onMouseUpdated(x, y, state);
    imageSelectedSection->onMouseUpdated(x, y, state);
}

/**
* Fun��o principal do programa.
*/
int main(void) {
   imagePanel = new ImagePanel(imagePanelX,imagePanelY,screenWidth - 5,screenHeight - 5);
   imageSelectedSection = new ImageSelectedSection(20, 5, imagePanel->getX1() - 20, screenHeight - 5, imagePanel->getSelectedImage());
   CV::init(screenWidth, screenHeight, "Trabalho 1");
   CV::run();
}
