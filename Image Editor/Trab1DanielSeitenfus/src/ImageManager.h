/**
 * @file ImageManager.h
 * @brief Defini��o da classe ImageManager para gerenciamento de imagens.
 *
 * Este arquivo cont�m a defini��o da classe ImageManager, respons�vel por gerenciar uma cole��o de imagens e as intera��es com elas, como adi��o, sele��o, manipula��o, dragging, drop, e renderiza��o.
 */

#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <vector>
#include "Panel.h"
#include "Image.h"
#define NO_IMAGE_SELECTED -1
using namespace std;

/**
 * Classe para gerenciamento de um conjunto de imagens.
 */
class ImageManager {

    vector<Image*> images;
    int selectedImageIndex = NO_IMAGE_SELECTED;
    bool draggingImage = false;
    Panel panel;

public:

    /**
     * Construtor da classe ImageManager.
     * @param _panel Painel para realiza��o de c�lculos referentes ao posicionamento das imagens.
     */
    ImageManager(Panel _panel) : panel(_panel) {
        images = {};
    }

    /**
     * Destrutor da classe ImageManager.
     */
    ~ImageManager() {
        for(int i=0; i<images.size(); i++) {
            free(images[i]);
        }
    }

    /**
     * Adiciona uma imagem ao gerenciador.
     * @param image Ponteiro para a imagem a ser adicionada.
     */
    void addImage(Image *image) {
        images.push_back(image);
    }

    /**
     * Inicializa a sele��o de imagem, selecionando a �ltima imagem adicionada.
     */
    void initializeImageSelection() {
        selectImage(getLastIndex());
    }

    /**
     * Renderiza todas as imagens.
     */
    void render() {
        for(int i=0; i<images.size(); i++) {
            images[i]->render();
        }
    }

    /**
     * Verifica se h� alguma imagem selecionada.
     * @return True se h� uma imagem selecionada, False caso contr�rio.
     */
    bool hasImageSelected() {
        return selectedImageIndex >= 0;
    }

    /**
     * @brief Trata os eventos do mouse. Se clicado, verifica se h� colis�o com as imagens e realiza os tratamentos necess�rios.
     * Se o clique for solto, desabilita o dragging da imagem. Em todos os casos, a fun��o de atualiza��o da posi��o da imagem � chamada.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @param state Estado de clique do mouse.
     */
     void onMouseUpdated(int mx, int my, int state) {
        if(state == 0) {
           checkImagesCollision(mx, my);
        } else if(state == 1) {
            draggingImage = false;
        }

        updateSelectedImagePosition(mx , my);
    }

    /**
     * Seleciona uma imagem com base no �ndice fornecido. Chama a fun��o que renderiza uma moldura na imagem.
     * @param index �ndice da imagem a ser selecionada.
     */
    void selectImage(int index) {
        setRenderPriority(index);
        images[getLastIndex()]->setSelected(true);
        selectedImageIndex = getLastIndex();
    }

    /**
     * Obt�m a imagem selecionada.
     * @return Ponteiro para a imagem selecionada.
     */
     Image* getSelectedImage() {
        if(!hasImageSelected()) {
            return NULL;
        }

        return images[selectedImageIndex];
    }

    /**
     * Inverte a imagem selecionada horizontalmente.
     */
    void flipHorizontally() {
        images[selectedImageIndex]->flipHorizontally();
    }

    /**
     * Inverte a imagem selecionada verticalmente.
     */
    void flipVertically() {
        if(!hasImageSelected()) {
            return;
        }
        images[selectedImageIndex]->flipVertically();
    }

    /**
     * Verifica se o gerenciador est� vazio (sem imagens adicionadas).
     * @return True se n�o h� imagens no gerenciador, False caso contr�rio.
     */
    bool isEmpty() {
        return images.empty();
    }

    /**
     * Obt�m a �ltima imagem adicionada.
     * @return Ponteiro para a �ltima imagem adicionada.
     */
    Image* getLastImage() {
        return images[getLastIndex()];
    }

private:

    /**
     *  Verifica colis�es com as imagens e processa sele��o. A checagem ocorre percorrendo da �ltima imagem at� a primeira, pois a �ltima possui prioridade de renderiza��o na tela (aparecer� na frente das outras).
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     */
    void checkImagesCollision(int mx, int my) {
         for(int i=images.size()-1; i>=0; i--) {
                if(images[i]->checkCollision(mx, my)) {
                    draggingImage = true;
                    if(i == selectedImageIndex) {
                        return;
                    }

                    if(i != selectedImageIndex) {
                        images[selectedImageIndex]->toggleSelected();
                    }

                    selectImage(i);
                    return; //Para a execu��o para evitar o processamento desncess�rio para outras imagens
                }
            }
    }

    /**
     * Atualiza a posi��o da imagem de acordo com a coordenada do mouse.
     S�o realizados alguns c�lculos para garantir que a imagem se mantenha dentro do painel.
        - Verifica��o se a imagem est� dentro do painel nos dois eixos. Caso sim, atualiza x e y
        - Caso n�o, algum eixo estar� fora do paniel. Para garantir fluidez no movimento, a fun��o atualiza apenas um dos eixos que ainda est� dentro do painel.
            Para o outro eixo, � realizado o c�lculo do tamanho m�ximo do painel - o tamanho da imagem (altura ou largura). Isso evita que a imagem fique travada caso o mouse se mova muito r�pido e o c�lculo retorna que a imagem est� fora.
            Por�m, a �ltima atualiza��o da imagem foi enquanto ainda sobrava espa�o entre a imagem e o painel. Ou seja, caso isso aconte�a, a fun��o for�a a atualiza��o, renderizando a imagem nas bordas do painel.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     */
    void updateSelectedImagePosition(int mx, int my) {
        if(draggingImage){

            if(isImageXInsidePanel(mx, my) && isImageYInsidePanel(mx, my)) {
                images[selectedImageIndex]->setPosition(mx, my);
                return;
            }

            if(isImageXInsidePanel(mx, my)) {
                if(my<panel.y1) {
                    images[selectedImageIndex]->setPosition(mx,panel.y1);
                } else {
                    images[selectedImageIndex]->setPosition(mx, panel.y2-images[selectedImageIndex]->getHeight());
                }
                return;
            }

            if(isImageYInsidePanel(mx, my)) {
                if(mx<panel.x1) {
                  images[selectedImageIndex]->setPosition(panel.x1, my);
                } else {
                    images[selectedImageIndex]->setPosition(panel.x2-images[selectedImageIndex]->getWidth(), my);
                }
                return;
            }
        }
    }

    /**
     * Verifica se a imagem est� dentro do painel no eixo x.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem est� dentro do painel no eixo x, False caso contr�rio.
     */
    bool isImageXInsidePanel(int mx, int my) {
        return mx >= panel.x1 && (mx + images[selectedImageIndex]->getWidth()) <= panel.x2;
    }

    /**
     * Verifica se a imagem est� dentro do painel no eixo y.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem est� dentro do painel no eixo y, False caso contr�rio.
     */
    bool isImageYInsidePanel(int mx, int my) {
        return my >= panel.y1 && (my + images[selectedImageIndex]->getHeight()) <= panel.y2;
    }

    /**
     * Verifica se a imagem est� dentro do painel.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem est� dentro do painel, False caso contr�rio.
     */
    bool isImageInsidePanel(int mx, int my) {
        Image *image = images[selectedImageIndex];
        return mx >= panel.x1 && (mx + image->getWidth()) <= panel.x2 && my >= panel.y1 && (my + image->getHeight()) <= panel.y2;
    }

    /**
     * Obt�m o �ndice da �ltima imagem no vetor.
     * @return �ndice da �ltima imagem no vetor.
     */
    int getLastIndex() {
        return images.size()-1;
    }

    /**
     * Define a prioridade de renderiza��o da imagem selecionada para que seja renderizada por cima das outras.
     * @param index �ndice da imagem a ser movida para a �ltima posi��o no vetor.
     */
    void setRenderPriority(int index) {
        if(index == getLastIndex()) return; //Se a imagem for a �ltima do vetor, nada precisa ser feito.
        Image *image = images[index];
        images.erase(images.begin() + index);
        images.push_back(image);
    }
};

#endif // IMAGEMANAGER_H_INCLUDED
