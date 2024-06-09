/**
* Trabalho 1 - Editor de Imagens - Computação Gráfica
*  Autor: Daniel Brenner Seitenfus
*         04/2024
*
* Features:
*   - Exibição de Bitmaps (24 bits) de qualquer resolução;
*   - Drag and drop de imagens dentro do painel;
*   - Alteração das cores da imagem, inclusive podendo combinar entre uma ou mais;
*   - Rotação (inversão) da imagem horizontal e verticalmente;
*   - Histograma dos canais R, G, B e Luminância, com dois estilos de visualização, alterado em tempo real;
*   - Alteração de brilho (escurer e clarear) da imagem por meio de um slider.
*   - Botões com ícones com fundo removido.
*
*  Instruções:
*    - O programa possui suporte para carregar N imagens. Por padrão, ele exibe 3, chamadas "a.bmp", "b.bmp" e "c.bmp". Para alterar as imagens, basta seguir esse padrão no diretório ./Imagens.
*	 - Para alterar as cores de uma imagem selecionada, clique nos botões R (vermelho), G (verde), B (azul) e L (escala de cinza).
*       Os botões R, G e B podem ser combinados.
*    - A cores da imagem também podem ser alteradas pressionando as teclas R, G, B e L do teclado.
*    - Para alterar o brilho da imagem, deslize o botão do slider para esquerda, para escurecer; para direita, para clarear.
*    - O histograma exibe os canais de cores de acordo com a seleção. Por default, R,G e B vêm selecionados.
*    - Para exibir o histograma de luminância da imagem basta clicar no botão L.
*    - O histograma possui dos modos de visualização, com os gráficos preenchidos ou "vazados". Isso pode ser alterado no botão "Preenchido" abaixo do histograma.
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
 * Função principal para renderizar o conteúdo do programa.
 */
void render() {
    imagePanel->render();
    imageSelectedSection->setImageSelected(imagePanel->getSelectedImage());
    imageSelectedSection->render();
}

/**
 * Função chamada quando uma tecla é pressionada.
 * @param key Código da tecla pressionada.
 */
void keyboard(int key) {
    imageSelectedSection->onKeyboardUpdated(key);
}

/**
 * Função chamada quando uma tecla é liberada.
 * @param key Código da tecla liberada.
 */
void keyboardUp(int key) {

}

/**
 * Função para tratar eventos do mouse: cliques, movimentos e rolagem.
 * @param button Botão do mouse pressionado.
 * @param state Estado de clique do mouse.
 * @param wheel Informação sobre rolagem.
 * @param direction Direção da roda do mouse.
 * @param x Coordenada x do mouse.
 * @param y Coordenada y do mouse.
 */
void mouse(int button, int state, int wheel, int direction, int x, int y) {
    imagePanel->onMouseUpdated(x, y, state);
    imageSelectedSection->onMouseUpdated(x, y, state);
}

/**
* Função principal do programa.
*/
int main(void) {
   imagePanel = new ImagePanel(imagePanelX,imagePanelY,screenWidth - 5,screenHeight - 5);
   imageSelectedSection = new ImageSelectedSection(20, 5, imagePanel->getX1() - 20, screenHeight - 5, imagePanel->getSelectedImage());
   CV::init(screenWidth, screenHeight, "Trabalho 1");
   CV::run();
}
