/**
 * @file ImageSelectedSection.h
 * @brief Defini��o da classe ImageSelectedSection para visualiza��o de uma imagem selecionada.
 *
 * Este arquivo cont�m a defini��o da classe ImageSelectedSection, que representa uma se��o de visualiza��o de uma imagem selecionada juntamente com controles relacionados, como bot�es de sele��o de canal de cor e um histograma.
 */


#ifndef IMAGESELECTEDVIEW_H_INCLUDED
#define IMAGESELECTEDVIEW_H_INCLUDED

#include "gl_canvas2d.h"
#include "Image.h"
#include "ButtonManager.h"
#include "Histogram.h"
#include "Slider.h"
#include "Text.h"

/**
 * Estrutura para armazenar informa��es sobre a imagem selecionada e as transforma��es aplicadas a ela.
 */
struct ImageSelectedContainer {
    int x1, y1, x2, y2;
    bool rSelected;
    bool gSelected;
    bool bSelected;
    bool lSelected;
    Image *image;

    /**
     * Aplica as op��es de canal de cor selecionadas � imagem.
     */
    void applyRgbOptions() {
        image->rSelected = rSelected;
        image->gSelected = gSelected;
        image->bSelected = bSelected;
        image->lSelected = lSelected;
    }

    /**
     * Centraliza a imagem dentro do cont�iner.
     */
    void centralizeImage() {
        int containerWidth = x2 - x1;
        int containerHeight = y2 - y1;
        int imageX = x1 + (containerWidth - image->getWidth())/2;
        int imageY = y1 + (containerHeight - image->getHeight())/2;
        image->setPosition(imageX, imageY);
    }
};

ImageSelectedContainer *imageSelected;
Histogram *histogram;
ButtonManager* buttonManager;

class ImageSelectedSection {
int width, height;
int x1, y1, x2, y2;
Slider *slider;
Text* sliderTitle;
Text* histogramTitle;
Text* histogramButtonLabel;

const int buttonWidth = 40;
const int buttonHeight = 40;
const int horizontalSpacing = 10;
const int verticalSpacing = 10;

public:

    /**
     * Construtor da se��o de imagem selecionada.
     * @param _x1 Coordenada x1 do canto superior esquerdo.
     * @param _y1 Coordenada y1 do canto superior esquerdo.
     * @param _x2 Coordenada x2 do canto inferior direito.
     * @param _y2 Coordenada y2 do canto inferior direito.
     * @param _image Ponteiro para a imagem selecionada.
     */
    ImageSelectedSection(int _x1, int _y1, int _x2, int _y2, Image *_image) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
        setupImageSelectedView(_image);
        setupSlider();
        setupHistogram();
        setupButtons();
        setupTexts();
    }

    /**
    * Fun��o para configurar a visualiza��o da imagem selecionada.
    * @param *_image Ponteiro para a imagem selecionada.
    */
    void setupImageSelectedView(Image *_image) {
        imageSelected = new ImageSelectedContainer();
        imageSelected->image = _image;
        imageSelected->x1 = x1;
        imageSelected->y1 = y2 - 250;
        imageSelected->x2 = x2;
        imageSelected->y2 = y2;

        imageSelected->rSelected = true;
        imageSelected->gSelected = true;
        imageSelected->bSelected = true;
        imageSelected->lSelected = false;

        if(_image != nullptr) {
            imageSelected->image = new Image(_image->getBmp(), x1, y1);
            imageSelected->image->setSelected(false);
            imageSelected->centralizeImage();
        }
    }

    /**
    * Fun��o que habilita/desabilita o canal de cor vermelho da imagem no clique do bot�o ou da tecla 'R'.
    */
    static void rButtonClick() {
        imageSelected->rSelected = !imageSelected->rSelected;
        imageSelected->lSelected = false;
        refreshButtons();
    }

    /**
    * Fun��o que habilita/desabilita o canal de cor verde da imagem no clique do bot�o ou da tecla 'G'.
    */
    static void gButtonClick() {
        imageSelected->gSelected = !imageSelected->gSelected;
        imageSelected->lSelected = false;
        refreshButtons();
    }

    /**
    * Fun��o que habilita/desabilita o canal de cor azul da imagem no clique do bot�o ou da tecla 'B'.
    */
    static void bButtonClick() {
        imageSelected->bSelected = !imageSelected->bSelected;
        imageSelected->lSelected = false;
        refreshButtons();
    }

    /**
    * Fun��o que habilita/desabilita a exibi��o da imagem em tons de cinza no clique do bot�o ou da tecla 'L'.
    */
    static void lButtonClick() {
        imageSelected->lSelected = !imageSelected->lSelected;
        imageSelected->rSelected = !imageSelected->lSelected;
        imageSelected->gSelected = !imageSelected->lSelected;
        imageSelected->bSelected = !imageSelected->lSelected;
        refreshButtons();
    }

    /**
    * Alterna o tipo de visualiza��o do histograma (preenchido ou vazado).
    */
    static void changeHistogramVisualization() {
        histogram->changeVisualizationOption();
        buttonManager->toggleSelectButton(4);
    }

    /**
    * Atualiza a visualiza��o dos bot�es de acordo com a sele��o de cores.
    */
    static void refreshButtons() {
        buttonManager->setSelectButton(0, imageSelected->rSelected);
        buttonManager->setSelectButton(1, imageSelected->gSelected);
        buttonManager->setSelectButton(2, imageSelected->bSelected);
        buttonManager->setSelectButton(3, imageSelected->lSelected);
    }

    /**
    * Cria um manager e configura todos os bot�es da "se��o de imagem selecionada".
    */
    void setupButtons() {
        buttonManager = new ButtonManager();
        setupRgbButtons();
        setupHistogramButton();
        refreshButtons();
    }

    /**
    * Configura os bot�es 'R', 'G', 'B' e 'L'.
    */
    void setupRgbButtons() {
        int x1Button = x1;
        int x2Button = x1Button + buttonWidth;
        int y1Button = imageSelected->y1 - buttonHeight - verticalSpacing;
        int y2Button = y1Button + buttonHeight;

        addRgbButton(&x1Button, &y1Button, &x2Button, &y2Button, "R", Color::RED, Color::WHITE, true, rButtonClick);
        addRgbButton(&x1Button, &y1Button, &x2Button, &y2Button, "G", Color::GREEN, Color::WHITE, true, gButtonClick);
        addRgbButton(&x1Button, &y1Button, &x2Button, &y2Button, "B", Color::BLUE, Color::WHITE, true, bButtonClick);
        addRgbButton(&x1Button, &y1Button, &x2Button, &y2Button, "L", Color::GREY, Color::WHITE, true, lButtonClick);
    }

    /**
    * Adiciona um bot�o do tipo 'RGB' ao manager de bot�es.
    */
    void addRgbButton(int* x1, int* y1, int* x2, int* y2, char* text, Color buttonColor, Color textColor, bool selectable, Func action) {
        buttonManager->addButton(*x1, *y1 , *x2, *y2, text, buttonColor, textColor, selectable, action);
        *x1 += buttonWidth + horizontalSpacing;
        *x2 += buttonWidth + horizontalSpacing;
    }

    /**
    * Configura o bot�o do histograma.
    */
    void setupHistogramButton() {
        buttonManager->addButton(histogram->x2 - 120, histogram->y1 - 18, histogram->x2 - 105, histogram->y1 - 7, " ", Color::GREY, Color::WHITE, true, changeHistogramVisualization);
        buttonManager->getLastButton()->setSelected(true);
    }

    /**
    * Configura a exibi��o do slider de brilho.
    */
    void setupSlider() {
        const int marginTop = 110;
        slider = new Slider(x1, imageSelected->y1 - marginTop, x2, imageSelected->y1 - marginTop, Color::BLACK, true);
    }

    /**
    * Configura a exibi��o do histograma.
    */
    void setupHistogram() {
        const int marginBottom = 40;
        const int histogramHeight = 50;
        histogram = new Histogram(x1, y1 + marginBottom, x2, slider->y1 - histogramHeight);
    }

    /**
    * Configura todos os textos desta se��o.
    */
    void setupTexts() {
        sliderTitle = new Text(slider->x1,slider->y2+20, "Brilho", Color::BLACK);
        histogramTitle = new Text(histogram->x1,histogram->y2+10, "Histograma", Color::BLACK);
        histogramButtonLabel = new Text(histogram->x2 - 100, histogram->y1 - 17, "Preenchido", Color::BLACK);
    }

    /**
    * Renderiza todos os elementos.
    */
    void render() {
       if(imageSelected->image != nullptr) imageSelected->image->render();
       buttonManager->render();
       if(histogram != nullptr){
            histogramTitle->render();
            histogram->render();
            histogramButtonLabel->render();
       }

       sliderTitle->render();
       slider->render();
    }

    /**
    * Aciona os eventos de mouse para o manager de bot�es e slider sempre que o mouse � movido ou clicado.
    */
    void onMouseUpdated(int mx, int my, int state) {
        buttonManager->onMouseUpdated(mx, my, state);
        slider->onMouseUpdated(mx, my, state);
    }

    /**
    * Aciona as fun��es de altera��o no canal de cores sempre que houver uma atualiza��o de teclado.
    */
    void onKeyboardUpdated(int key) {
        if(key == 114) { //R
            rButtonClick();
        } else if (key == 103) { //G
            gButtonClick();
        } else if (key == 98) { //B
            bButtonClick();
        } else if (key == 108) { // L
            lButtonClick();
        }
    }

    /**
    * Atribui uma nova imagem selecionada � esta se��o.
    * @param *_image Ponteiro para a imagem selecionada.
    */
    void setImageSelected(Image *_image) {
        if(_image != nullptr) {
            imageSelected->image = new Image(_image, x1, y1);
            imageSelected->applyRgbOptions();
            imageSelected->centralizeImage();
            imageSelected->image->setLightness(slider->getValueByPosition()*-1);
            imageSelected->image->setSelected(false);
            if(histogram != nullptr) histogram->setImage(imageSelected->image);
        }
    }
};

#endif // IMAGESELECTEDVIEW_H_INCLUDED
