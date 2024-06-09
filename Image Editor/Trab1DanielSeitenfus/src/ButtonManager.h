/**
 * @file ButtonManager.h
 * @brief Definição da classe ButtonManager para gerenciamento de botões.
 *
 * Este arquivo contém a definição da classe ButtonManager, responsável por gerenciar uma coleção de botões e as interações com eles, como adição, renderização e tratamento de eventos de mouse.
 */

#ifndef BUTTONMANAGER_H_INCLUDED
#define BUTTONMANAGER_H_INCLUDED

#include <vector>
#include <functional>
#include "Button.h"
#include "Color.h"

#define NO_BUTTON_SELECTED -1

/**
 * Classe para gerenciamento de botões.
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
     * Adiciona um botão ao gerenciador.
     * @param x Coordenada x do canto superior esquerdo do botão.
     * @param y Coordenada y do canto superior esquerdo do botão.
     * @param larg Largura do botão.
     * @param alt Altura do botão.
     * @param text Texto do botão.
     * @param buttonColor Cor do botão.
     * @param textColor Cor do texto do botão.
     * @param selectable Indica se o botão pode ser selecionado.
     * @param _action Função de ação associada ao botão.
     */
    void addButton(int x, int y, int larg, int alt, char* text, Color buttonColor, Color textColor, bool selectable, Func _action) {
        buttons.push_back(new Button(x, y, larg, alt, text, buttonColor, textColor, selectable, _action));
    }

    /**
     * Adiciona um botão com ícone ao gerenciador.
     * @param x Coordenada x do canto superior esquerdo do botão.
     * @param y Coordenada y do canto superior esquerdo do botão.
     * @param larg Largura do botão.
     * @param alt Altura do botão.
     * @param text Texto do botão.
     * @param buttonColor Cor do botão.
     * @param textColor Cor do texto do botão.
     * @param selectable Indica se o botão pode ser selecionado.
     * @param fileName Nome do arquivo de ícone do botão.
     * @param _action Função de ação associada ao botão.
     */
    void addButton(int x, int y, int larg, int alt, char* text, Color buttonColor, Color textColor, bool selectable, const char *fileName, Func _action) {
        buttons.push_back(new Button(x, y, larg, alt, text, buttonColor, textColor, selectable, fileName, _action));
    }

    /**
     * Renderiza todos os botões.
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
     * Alterna a seleção do botão.
     * @param index Índice do botão.
     */
    void toggleSelectButton(int index) {
        buttons[index]->toggleSelected();
    }

    /**
     * Define o estado de seleção de um botão.
     * @param index Índice do botão.
     * @param selected True para selecionar o botão, False para deselecioná-lo.
     */
    void setSelectButton(int index, bool selected) {
        buttons[index]->setSelected(selected);
    }

    /**
     * Obtém o último botão adicionado.
     * @return Ponteiro para o último botão adicionado.
     */
    Button* getLastButton() {
        return buttons[buttons.size()-1];
    }

    /**
     * Obtém um botão pelo seu índice.
     * @param index Índice do botão.
     * @return Ponteiro para o botão correspondente ao índice.
     */
     Button* getButton(int index) {
        if(index >= buttons.size()) return nullptr;
        return buttons[index];
     }
};

#endif // BUTTONMANAGER_H_INCLUDED
