#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath>
#include <cstdio>

class Vector2 {
public:
   float x, y;

   Vector2(){
      x = y = 0;
   }

   Vector2(float _x, float _y){
       x = _x;
       y = _y;
   }

   void set(float _x, float _y){
       x = _x;
       y = _y;
   }

   void normalize(){
       float norm = std::sqrt(x*x + y*y);

       if(norm == 0.0){
          printf("\n\nNormalize::Divisao por zero");
          x = 1;
          y = 1;
          return;
       }
       x /= norm;
       y /= norm;
   }

   Vector2 operator - (const Vector2& v){
        Vector2 aux( x - v.x, y - v.y);
        return ( aux );
   }

   Vector2 operator + (const Vector2& v){
       Vector2 aux( x + v.x, y + v.y);
       return ( aux );
   }

   // Adicionem os demais overloads de operadores aqui.
    Vector2 operator * (float scalar) const { // multiplicação por escalar
        Vector2 aux(x * scalar, y * scalar);
        return ( aux );
    }

    Vector2& operator += (const Vector2& v) { // soma e atribuição
        x += v.x;
        y += v.y;
        return *this;
    }

    bool operator == (const Vector2& v) { // soma e atribuição
        return x == v.x && y == v.y;
    }

    float dot(const Vector2& v) const { // produto escalar
        return x * v.x + y * v.y;
    }

    float cross(const Vector2& v) const { // produto vetorial
       return x * v.y - y * v.x;
    }

    float distance(const Vector2& v) {
        float dx = v.x - x;
        float dy = v.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vector2 direction(const Vector2& v) {
        float dx = v.x - x;
        float dy = v.y - y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist != 0) {
            return Vector2(dx / dist, dy / dist);
        }
        return Vector2(0, 0);
    }

    float angle(const Vector2& v1, const Vector2& v2) {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        return std::atan2(dy, dx);
    }


    Vector2 perpendicular() const {
        // Retorna um vetor perpendicular ao vetor atual
        return Vector2(-y, x);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }


};

#endif
