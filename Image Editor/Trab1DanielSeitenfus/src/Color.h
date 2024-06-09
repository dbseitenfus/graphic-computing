/**
 * @file Color.h
 * @brief Define a classe Color, que abstrai a definição de cores RGB. Isso abstrai complexidade do restante do código, melhora a refatoração do projeto e legibilidade do código.
 * É muito mais fácil identificar uma cor por nome, do que por inteiros.
 */

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

/**
 * Classe para representar cores RGB.
 */
class Color {
public:
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color WHITE;
    static const Color GREY;
    static const Color BLACK;
    static const Color YELLOW;

    float r, g, b, alpha;

private:
    /**
     * Construtor da classe Color.
     * @param _r Componente vermelho da cor.
     * @param _g Componente verde da cor.
     * @param _b Componente azul da cor.
     */

    Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {
        alpha = 1;
    }

    /**
     * Construtor da classe Color.
     * @param _r Componente vermelho da cor.
     * @param _g Componente verde da cor.
     * @param _b Componente azul da cor.
     * @param _alpha Valor de opacidade da cor.
     */
    Color(float _r, float _g, float _b, float _alpha) : r(_r), g(_g), b(_b), alpha(_alpha) {}
};

const Color Color::RED(1, 0, 0);
const Color Color::GREEN(0, 1, 0);
const Color Color::BLUE(0, 0, 1);
const Color Color::WHITE(1, 1, 1);
const Color Color::GREY(0.8, 0.8, 0.8);
const Color Color::BLACK(0, 0, 0);
const Color Color::YELLOW(1, 1, 0);

#endif // COLOR_H_INCLUDED
