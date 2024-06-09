/**
 * @file ImageManager.h
 * @brief Definição da classe ImageManager para gerenciamento de imagens.
 *
 * Este arquivo contém a definição da classe ImageManager, responsável por gerenciar uma coleção de imagens e as interações com elas, como adição, seleção, manipulação, dragging, drop, e renderização.
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
     * @param _panel Painel para realização de cálculos referentes ao posicionamento das imagens.
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
     * Inicializa a seleção de imagem, selecionando a última imagem adicionada.
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
     * Verifica se há alguma imagem selecionada.
     * @return True se há uma imagem selecionada, False caso contrário.
     */
    bool hasImageSelected() {
        return selectedImageIndex >= 0;
    }

    /**
     * @brief Trata os eventos do mouse. Se clicado, verifica se há colisão com as imagens e realiza os tratamentos necessários.
     * Se o clique for solto, desabilita o dragging da imagem. Em todos os casos, a função de atualização da posição da imagem é chamada.
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
     * Seleciona uma imagem com base no índice fornecido. Chama a função que renderiza uma moldura na imagem.
     * @param index Índice da imagem a ser selecionada.
     */
    void selectImage(int index) {
        setRenderPriority(index);
        images[getLastIndex()]->setSelected(true);
        selectedImageIndex = getLastIndex();
    }

    /**
     * Obtém a imagem selecionada.
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
     * Verifica se o gerenciador está vazio (sem imagens adicionadas).
     * @return True se não há imagens no gerenciador, False caso contrário.
     */
    bool isEmpty() {
        return images.empty();
    }

    /**
     * Obtém a última imagem adicionada.
     * @return Ponteiro para a última imagem adicionada.
     */
    Image* getLastImage() {
        return images[getLastIndex()];
    }

private:

    /**
     *  Verifica colisões com as imagens e processa seleção. A checagem ocorre percorrendo da última imagem até a primeira, pois a última possui prioridade de renderização na tela (aparecerá na frente das outras).
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
                    return; //Para a execução para evitar o processamento desncessário para outras imagens
                }
            }
    }

    /**
     * Atualiza a posição da imagem de acordo com a coordenada do mouse.
     São realizados alguns cálculos para garantir que a imagem se mantenha dentro do painel.
        - Verificação se a imagem está dentro do painel nos dois eixos. Caso sim, atualiza x e y
        - Caso não, algum eixo estará fora do paniel. Para garantir fluidez no movimento, a função atualiza apenas um dos eixos que ainda está dentro do painel.
            Para o outro eixo, é realizado o cálculo do tamanho máximo do painel - o tamanho da imagem (altura ou largura). Isso evita que a imagem fique travada caso o mouse se mova muito rápido e o cálculo retorna que a imagem está fora.
            Porém, a última atualização da imagem foi enquanto ainda sobrava espaço entre a imagem e o painel. Ou seja, caso isso aconteça, a função força a atualização, renderizando a imagem nas bordas do painel.
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
     * Verifica se a imagem está dentro do painel no eixo x.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem está dentro do painel no eixo x, False caso contrário.
     */
    bool isImageXInsidePanel(int mx, int my) {
        return mx >= panel.x1 && (mx + images[selectedImageIndex]->getWidth()) <= panel.x2;
    }

    /**
     * Verifica se a imagem está dentro do painel no eixo y.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem está dentro do painel no eixo y, False caso contrário.
     */
    bool isImageYInsidePanel(int mx, int my) {
        return my >= panel.y1 && (my + images[selectedImageIndex]->getHeight()) <= panel.y2;
    }

    /**
     * Verifica se a imagem está dentro do painel.
     * @param mx Coordenada x do mouse.
     * @param my Coordenada y do mouse.
     * @return True se a imagem está dentro do painel, False caso contrário.
     */
    bool isImageInsidePanel(int mx, int my) {
        Image *image = images[selectedImageIndex];
        return mx >= panel.x1 && (mx + image->getWidth()) <= panel.x2 && my >= panel.y1 && (my + image->getHeight()) <= panel.y2;
    }

    /**
     * Obtém o índice da última imagem no vetor.
     * @return Índice da última imagem no vetor.
     */
    int getLastIndex() {
        return images.size()-1;
    }

    /**
     * Define a prioridade de renderização da imagem selecionada para que seja renderizada por cima das outras.
     * @param index Índice da imagem a ser movida para a última posição no vetor.
     */
    void setRenderPriority(int index) {
        if(index == getLastIndex()) return; //Se a imagem for a última do vetor, nada precisa ser feito.
        Image *image = images[index];
        images.erase(images.begin() + index);
        images.push_back(image);
    }
};

#endif // IMAGEMANAGER_H_INCLUDED
