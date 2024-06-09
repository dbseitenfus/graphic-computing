/**
 * @file Button.h
 * @brief Defini��o da classe Button para representar um bot�o.
 *
 * Este arquivo cont�m a defini��o da classe Button, que representa um bot�o na tela, podendo conter um r�tulo de texto e/ou um �cone.
 */


#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "Color.h"
#include "Math.h"
#include "Text.h"

typedef void (*Func)();

/**
 * Classe para representar um bot�o na tela.
 */
class Button {
  Color buttonColor;
  Text* text;
  Func action;
  Image *icon;
  bool selectable;
  bool selected;
  const Color frameColor = Color::BLACK;
  const int frameWidth = 3;

public:
  float x1, y1, x2, y2;

  /**
     * @brief Construtor da classe Button.
     * @param _x1 Coordenada x1.
     * @param _y1 Coordenada y1.
     * @param _x2 Coordenada x2.
     * @param _y2 Coordenada y2.
     * @param _label R�tulo de texto do bot�o.
     * @param _buttonColor Cor do bot�o.
     * @param _textColor Cor do texto do bot�o.
     * @param _selectable Indicador de selecionabilidade do bot�o.
     * @param _action Fun��o de a��o do bot�o.
     */
  Button(float _x1, float _y1, float _x2, float _y2, const char *_label, Color _buttonColor, Color _textColor, bool _selectable, Func _action)
      : x1(_x1), y1(_y1), x2(_x2), y2(_y2), buttonColor(_buttonColor), selectable(_selectable), action(_action) {
     text = new Text(x1+5, y1+((y2-y1)/2), _label, _textColor);
     selected = false;
  }

  /**
     *  Construtor da classe Button com �cone.
     * @param _x1 Coordenada x1.
     * @param _y1 Coordenada y1.
     * @param _x2 Coordenada x2.
     * @param _y2 Coordenada y2.
     * @param _label R�tulo de texto do bot�o.
     * @param _buttonColor Cor do bot�o.
     * @param _textColor Cor do texto do bot�o.
     * @param _selectable Indicador de selecionabilidade do bot�o.
     * @param fileName Nome do arquivo do �cone.
     * @param _action Fun��o de a��o do bot�o.
     */
  Button(float _x1, float _y1, float _x2, float _y2, const char *_label, Color _buttonColor, Color _textColor, bool _selectable, const char *fileName, Func _action)
      : x1(_x1), y1(_y1), x2(_x2), y2(_y2), buttonColor(_buttonColor), selectable(_selectable), action(_action) {
     text = new Text(x1+5, y1+((y2-y1)/2), _label, _textColor);
     selected = false;
     setIconCentralized(new Bmp(fileName));
  }

  /**
     * Define o �cone centralizado no bot�o.
     * @param bmp Ponteiro para o objeto Bmp contendo os dados do �cone.
     */
  void setIconCentralized(Bmp *bmp) {
      int imageX2 = x1 + bmp->getWidth();
      int imageY2 = y1 + bmp->getHeight();

      int imageWidth = imageX2 - x1;
      int imageHeight = imageY2 - y1;

      int iconX = x1 + (getWidth() - imageWidth)/2;
      int iconY = y1 + (getHeight() - imageHeight)/2;

      icon = new Image(bmp,iconX, iconY);
      icon->setTransparency(true);
  }

  /**
  * Renderiza o bot�o na tela.
  */
  void render() {
      if(selectable && selected) renderFrame();

      CV::color(buttonColor.r, buttonColor.g, buttonColor.b);
      CV::rectFill(x1, y1, x2, y2);

      if(icon != nullptr) {
        icon->render();
      } else {
        text->render();
      }
  }

  /**
  * Renderiza a moldura do bot�o quando selecionado.
  */
  void renderFrame() {
    CV::color(frameColor.r, frameColor.g, frameColor.b);
    for(int i=0; i<frameWidth; i++) {
        CV::rect(x1-i, y1-i, x2+i, y2+i);
    }
  }

  /**
  * Verifica se um ponto est� dentro da �rea ocupada pelo bot�o.
  * @param mx Coordenada x do ponto.
  * @param my Coordenada y do ponto.
  * @return true se o ponto est� dentro da �rea do bot�o, false caso contr�rio.
  */
  bool colidiu(int mx, int my) {
      return Math::isPointInsideRectangle(mx, my, x1, y1, x2, y2);
  }

  /**
  * Executa a a��o do bot�o quando clicado.
  */
  void onClick(){
    action();
  }

  /**
  * Define se o bot�o est� selecionado ou n�o.
  * @param _selected Indicador de sele��o do bot�o.
  */
  void setSelected(bool _selected) {
    selected = _selected;
  }

  /**
  * Alterna o estado de sele��o do bot�o.
  */
  void toggleSelected() {
    selected = !selected;
  }

  /**
  * Obt�m a altura do bot�o.
  * @return A altura do bot�o.
  */
  int getHeight() {
    return y2 - y1;
  }

  /**
  * @brief Obt�m a largura do bot�o.
  * @return A largura do bot�o.
  */
  int getWidth() {
    return x2 - x1;
  }

};

#endif
