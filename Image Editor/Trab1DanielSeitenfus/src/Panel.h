/**
 * @file Panel.h
 * @brief Definição da estrutura Panel para representar um painel retangular.
 *
 * Este arquivo contém a definição da estrutura Panel, que representa um painel retangular definido pelas coordenadas de seus cantos.
 */

#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

/**
 * Estrutura para representar um painel retangular.
 */
struct Panel {
    int x1;
    int y1;
    int x2;
    int y2;

    Panel(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
    }

    /**
    * Renderize a moldura do painel.
    */
    void render() {
        CV::color(0,0,0);
        CV::rect(x1, y1, x2, y2);
    }
};

#endif // PANEL_H_INCLUDED
