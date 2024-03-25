#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "Color.h"

class Button {
  float altura, largura, x, y;
  char label[100];
  Color buttonColor;
  Color textColor;

  //std::function<void()> action;

public:
  Button(float _x, float _y, float _larg, float _alt, char *_label, Color _buttonColor, Color _textColor)
      : x(_x), y(_y), largura(_larg), altura(_alt), buttonColor(_buttonColor), textColor(_textColor) {
     strcpy(label, _label);
  }

  void render() {
      CV::color(buttonColor.r, buttonColor.g, buttonColor.b);
      CV::rectFill(x, y, x + largura, y + altura);
      CV::color(textColor.r, textColor.g, textColor.b);
      CV::text(x+5, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool colidiu(int mx, int my) {
      return mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura);
  }

};

#endif
