/**
 * @file ButtonManager.h
 * @brief Defini��o da classe ButtonManager para gerenciamento de bot�es.
 *
 * Este arquivo cont�m a defini��o da classe ButtonManager, respons�vel por gerenciar uma cole��o de bot�es e as intera��es com eles, como adi��o, renderiza��o e tratamento de eventos de mouse.
 */

#ifndef BUTTONMANAGER_H_INCLUDED
#define BUTTONMANAGER_H_INCLUDED

#include <vector>
#include <functional>
#include "Button.h"
#include "Color.h"

#define NO_BUTTON_SELECTED -1

/**
 * Classe para gerenciamento de bot�es.
 */
class ButtonManager {

public:
    std::vector<Button*> buttons;
    Func action;
    int selectedIndex;

    /**
     * Construtor da classe ButtonManager.
     */
    ButtonManager() {
        buttons = {};
        selectedIndex = NO_BUTTON_SELECTED;
    }

    /**
     * Destrutor da classe ButtonManager.
     */
    ~ButtonManager() {
        for(int i=0; i<buttons.size(); i++) {
            free(buttons[i]);
        }
    }

    /**
     * Adiciona um bot�o ao gerenciador.
     * @param x Coordenada x do canto superior esquerdo do bot�o.
     * @param y Coordenada y do canto superior esquerdo do bot�o.
     * @param larg Largura do bot�o.
     * @param alt Altura do bot�o.
     * @param text Texto do bot�o.
     * @param buttonColor Cor do bot�o.
     * @param textColor Cor do texto do bot�o.
     * @param selectable Indica se o bot�o pode ser selecionado.
     * @param _action Fun��o de a��o associada ao bot�o.
     */
    void addButton(int x, int y, int larg, int alt, char* text, Color buttonColor, Color textColor, bool selectable, Func _action) {
        buttons.push_back(new Button(x, y, larg, alt, text, buttonColor, textColor, selectable, _action));
    }

    /**
     * Adiciona um bot�o com �cone ao gerenciador.
     * @param x Coordenada x do canto superior esquerdo do bot�o.
     * @param y Coordenada y do canto superior esquerdo do bot�o.
     * @param larg Largura do bot�o.
     * @param alt Altura do bot�o.
     * @param text Texto do bot�o.
     * @param buttonColor Cor do bot�o.
     * @param textColor Cor do texto do bot�o.
     * @param selectable Indica se o bot�o pode ser selecionado.
     * @param fileName Nome do arquivo de �cone do bot�o.
     * @param _action Fun��o de a��o associada ao bot�o.
     */
    void addButton(int x, int y, int larg, int alt, char* text, Color buttonColor, Color textColor, bool selectable, const char *fileName, Func _action) {
        buttons.push_back(new Button(x, y, larg, alt, text, buttonColor, textColor, selectable, fileName, _action));
    }

    /**
     * Renderiza todos os bot�es.
     */
    void render() {
        for(int i=0; i<buttons.size(); i++) {
            buttons[i]->render();
        }
    }

    /**
     * @brief Trata os eventos do mouse.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @param state Estado de clique do mouse.
     */
    void onMouseUpdated(int mx, int my, int state) {
        if(state == 0) {
            for(int i=0; i<buttons.size(); i++) {
                if(buttons[i]->colidiu(mx, my)) {
                    buttons[i]->onClick();
                    return;
                }
            }
        }
    }

    /**
     * Alterna a sele��o do bot�o.
     * @param index �ndice do bot�o.
     */
    void toggleSelectButton(int index) {
        buttons[index]->toggleSelected();
    }

    /**
     * Define o estado de sele��o de um bot�o.
     * @param index �ndice do bot�o.
     * @param selected True para selecionar o bot�o, False para deselecion�-lo.
     */
    void setSelectButton(int index, bool selected) {
        buttons[index]->setSelected(selected);
    }

    /**
     * Obt�m o �ltimo bot�o adicionado.
     * @return Ponteiro para o �ltimo bot�o adicionado.
     */
    Button* getLastButton() {
        return buttons[buttons.size()-1];
    }

    /**
     * Obt�m um bot�o pelo seu �ndice.
     * @param index �ndice do bot�o.
     * @return Ponteiro para o bot�o correspondente ao �ndice.
     */
     Button* getButton(int index) {
        if(index >= buttons.size()) return nullptr;
        return buttons[index];
     }
};

#endif // BUTTONMANAGER_H_INCLUDED
