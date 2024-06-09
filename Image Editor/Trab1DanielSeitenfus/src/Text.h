/**
 * @file Text.h
 * @brief Definição da classe Text para renderização de texto na tela.
 *
 * Este arquivo contém a definição da classe Text, que é utilizada para renderizar texto na tela.
 */

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Color.h"
#include "gl_canvas2d.h"

/**
 * Classe para renderização de texto na tela.
 */
class Text {
public:
    int x;
    int y;
    const char* text;
    Color color;

    /**
     *  Construtor da classe Text.
     * @param _x Coordenada x do texto.
     * @param _y Coordenada y do texto.
     * @param _text Texto a ser renderizado.
     * @param _color Cor do texto.
     */
    Text(int _x, int _y, const char* _text, Color _color) : x(_x), y(_y), text(_text), color(_color) {}

    /**
     * Renderiza o texto na tela.
     */
    void render() {
        CV::color(color.r, color.g, color.b);
        CV::text(x, y, text);
    }
};

#endif // TEXT_H_INCLUDED
