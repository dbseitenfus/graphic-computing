/**
 * @file ImagePanel.h
 * @brief Definição da classe ImagePanel para representar um painel de exibição de imagens.
 *
 * Este arquivo contém a definição da classe ImagePanel, que é responsável por criar e gerenciar o painel de exibição de imagens.
 * O painel pode exibir várias imagens carregadas a partir de arquivos BMP e fornece funcionalidades para interagir com essas imagens, como virar horizontalmente ou verticalmente, além de permitir a seleção e manipulação das mesmas.
 * O painel também faz o controle de posicionamento das imagens, impedindo que elas sejam arrastadas para fora da dimensão do painel.
 */

#ifndef IMAGEPANEL_H_INCLUDED
#define IMAGEPANEL_H_INCLUDED

#include "gl_canvas2d.h"
#include "ImageManager.h"
#include "Bmp.h"
#include "Image.h"
#include "Math.h"
#include "ButtonManager.h"
#include <functional>

ImageManager *imageManager;
int xAux, yAux;
bool showHint1;

/**
 * Classe que representa um painel de exibição de imagens.
 */
class ImagePanel {
ButtonManager *buttonManager;
Panel panel;

public:
    /**
     * Construtor da classe ImagePanel.
     * @param x1 Coordenada x1
     * @param y1 Coordenada y1.
     * @param x2 Coordenada x2.
     * @param y2 Coordenada y2.
     */
    ImagePanel(int x1, int y1, int x2, int y2) : panel(x1, y1, x2, y2) {
        imageManager = new ImageManager(panel);
        buttonManager = new ButtonManager();
        setupButtons();
        xAux = panel.x1;
        yAux = panel.y1;
        showHint1 = true;
    }

    /**
     * Renderiza o painel de exibição de imagens.
     */
    void render() {
        panel.render();
        imageManager->render();
        buttonManager->render();
        if(showHint1) renderStartHint();
    }

    /**
     * Carrega imagens para exibição no painel e desabilita a exibição da dica 1.
     */
    static void loadImages() {
        if(!imageManager->isEmpty()) return;

        showHint1 = false;
        addImage(".\\Trab1DanielSeitenfus\\images\\a.bmp");
        addImage(".\\Trab1DanielSeitenfus\\images\\b.bmp");
        addImage(".\\Trab1DanielSeitenfus\\images\\c.bmp");
        initializeImageSelection();
    }

    /**
     * Adiciona uma imagem ao painel.
     * @param fileName Nome do arquivo da imagem.
     */
    static void addImage(const char *fileName) {
        imageManager->addImage(new Image(new Bmp(fileName), xAux, yAux));
        xAux += imageManager->getLastImage()->getWidth()/2;
        yAux += imageManager->getLastImage()->getHeight()-10;
    }

    /**
     * Inverte a imagem horizontalmente.
     */
    static void flipImageHorizontally() {
        imageManager->flipHorizontally();
    }

    /**
     * Inverte a imagem verticalmente.
     */
    static void flipImageVertically() {
        imageManager->flipVertically();
    }

    /**
     * Configura todos os botões do painel.
     */
    void setupButtons() {
        const int spacing = 1;
        const int buttonSize = 50;
        int x1Button = panel.x2-buttonSize;
        int y1Button = panel.y2-buttonSize;
        int x2Button = panel.x2-spacing;
        int y2Button = panel.y2-spacing;

        buttonManager->addButton(x1Button, y1Button, x2Button, y2Button, "", Color::GREY, Color::BLACK, false, ".\\Trab1DanielSeitenfus\\images\\icons\\addimages.bmp", loadImages);
        y1Button -= buttonSize - spacing;
        buttonManager->addButton(x1Button, y1Button, x2Button, buttonManager->getLastButton()->y1 - spacing, "", Color::GREY, Color::BLACK, false, ".\\Trab1DanielSeitenfus\\images\\icons\\flipvertical.bmp", flipImageVertically);
        y1Button -= buttonSize - spacing;
        buttonManager->addButton(x1Button, y1Button, x2Button, buttonManager->getLastButton()->y1 - spacing, "", Color::GREY, Color::BLACK, false, ".\\Trab1DanielSeitenfus\\images\\icons\\fliphorizontal.bmp", flipImageHorizontally);
    }

    /**
     * Inicializa a seleção de imagem no painel, selecionando a última imagem adicionada.
     */
    static void initializeImageSelection() {
        imageManager->initializeImageSelection();
    }

    /**
     * Trata os eventos do mouse, chamando os eventos correspondentes do manager de imagens e botões.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @param state Estado de clique do mouse.
     */
    void onMouseUpdated(int mx, int my, int state) {
        imageManager->onMouseUpdated(mx, my, state);
        buttonManager->onMouseUpdated(mx, my, state);
    }

    /**
     * Verifica se o mouse está dentro do painel.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se o mouse está dentro do painel, False caso contrário.
     */
    bool isMouseInsidePanel(int mx, int my) {
        return Math::isPointInsideRectangle(mx, my, panel.x1, panel.y1, panel.x2, panel.y2);
    }

    /**
     * Obtém a imagem selecionada no painel.
     * @return Ponteiro para a imagem selecionada.
     */
    Image* getSelectedImage() {
        return imageManager->getSelectedImage();
    }

    /**
     * Renderiza a dica inicial.
     */
    void renderStartHint() {
        Color color = Color::YELLOW;
        CV::color(color.r, color.g, color.b);
        CV::rectFill(panel.x2-50-340,panel.y2-10,  panel.x2-55, panel.y2-35);
        color = Color::BLACK;
        CV::color(color.r, color.g, color.b);
        CV::text(panel.x2-50-335,panel.y2-25, "Dica: Clique aqui para iniciar ->");
    }

    /**
     * Obtém a coordenada x do canto inferior esquerdo do painel.
     * @return Coordenada x do canto inferior esquerdo do painel.
     */
    int getX1() {
        return panel.x1;
    }
};


#endif // IMAGEPANEL_H_INCLUDED
