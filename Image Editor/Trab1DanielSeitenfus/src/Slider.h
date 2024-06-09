/**
 * @file Slider.h
 * @brief Definição da classe Slider para criação e manipulação de um controle deslizante.
 *
 * Este arquivo contém a definição da classe Slider, responsável por representar um controle deslizante na interface gráfica.
 */

#ifndef SLIDER_H_INCLUDED
#define SLIDER_H_INCLUDED

#include "Math.h"

/**
 * Classe para representar o botão deslizante de um slider.
 */
class SliderHandle {

public:
    int x1;
    int y1;
    int radius;
    Color color;

    /**
     * Construtor da classe SliderHandle.
     * @param _x1 Coordenada x do botão deslizante.
     * @param _y1 Coordenada y do botão deslizante.
     * @param _radius Raio do botão deslizante.
     * @param _color Cor do botão deslizante.
     */
    SliderHandle(int _x1, int _y1, int _radius, Color _color) : x1(_x1), y1(_y1), radius(_radius), color(_color) {}
};

/**
 * Classe para representar um controle deslizante.
 */
class Slider {
    Color color;
    bool dragging;
    SliderHandle *sliderHandle;
    float maxValue;
    float interval;
    float value;
    bool allowNegativeValues;
    int initialValuePosition;

public:
    int x1, y1, x2, y2;

     /**
     * @brief Construtor da classe Slider.
     * @param _x1 Coordenada x do ponto inicial.
     * @param _y1 Coordenada y do ponto inicial.
     * @param _x2 Coordenada x do ponto final.
     * @param _y2 Coordenada y do ponto final.
     * @param _color Cor do botão deslizante.
     * @param _allowNegativeValues Indica se valores negativos são permitidos.
     */
    Slider(int _x1, int _y1, int _x2, int _y2, Color _color, bool _allowNegativeValues) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), color(_color), allowNegativeValues(_allowNegativeValues) {
        dragging = false;

        initialValuePosition = allowNegativeValues ? x2/2 : x1;
        sliderHandle = new SliderHandle(initialValuePosition, y1, 8, color);

        maxValue = 1;
        interval = maxValue/(x2-initialValuePosition);
    }

    /**
     * Renderiza o controle deslizante.
     */
    void render() {
        CV::color(color.r, color.g, color.b);
        CV::line(x1, y1, x2, y2);
        CV::circleFill(sliderHandle->x1, sliderHandle->y1, sliderHandle->radius, 25);
    }

    /**
     * Verifica a colisão do mouse com o botão do slider.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se houve colisão, False caso contrário.
     */
    bool checkCollision(int mx, int my) {
        int dist = Math::distance(mx, my, sliderHandle->x1, sliderHandle->y1);
        return dist <= sliderHandle->radius;
    }

    /**
     * Obtém o valor do slider com base na posição do botão.
     * @return Valor do slider.
     */
    float getValueByPosition() {
        float position = sliderHandle->x1 - initialValuePosition;
        return position * interval;
    }

    /**
     * Atualiza a posição do botão deslizante com base na interação do mouse.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @param state Estado do mouse.
     */
    void onMouseUpdated(int mx, int my, int state) {
        if(dragging) {
            if(mx >= x2) {
                sliderHandle->x1 = x2;
            } else if(mx <= x1) {
                sliderHandle->x1 = x1;
            } else {
                sliderHandle->x1 = mx;
            }
        }

        if(state == 0) {
            if(checkCollision(mx, my)) {
                dragging = true;
            }

        } else if(state == 1) {
            dragging = false;
        }
    }

};

#endif // SLIDER_H_INCLUDED
