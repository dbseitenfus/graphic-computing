#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <math.h>

/**
 * Classe utilitária para operações matemáticas simples.
 */
class Math {
public:
     /**
     * Calcula a distância entre dois pontos.
     */
    static float distance(int x1, int y1, int x2, int y2) {
        return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    }

    /**
     * Verifica se um ponto está dentro de um retângulo.
     */
    static bool isPointInsideRectangle(int pointX, int pointY, int x1, int y1, int x2, int y2) {
        return pointX >= x1 && pointX <= x2 && pointY >= y1 && pointY <= y2;
    }

};


#endif // MATH_H_INCLUDED
