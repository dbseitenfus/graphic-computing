/**
 * @file Image.h
 * @brief Definição da classe Image para representar uma imagem.
 *
 * Este arquivo contém a definição da classe Image, que representa uma imagem bitmap (BMP) e suas propriedades, como posição, seleção, efeitos de visualização, entre outros.
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Bmp.h"
using namespace std;

class Image {


public:
    int x, y, selected;
    int frameWidth = 5;
    Bmp *bmp;
    float lightness;
    bool transparency; /**<Se true, não exibe a cor branca. É uma definição para exibição dos ícones. Por padrão, todos arquivos de ícone do projeto possuem fundo branco e são removidos na exibição.*/
    bool flippedHorizontally;
    bool flippedVertically;

    bool rSelected, gSelected, bSelected, lSelected;

    //Auxiliares de renderização. Foram declaradas globalmente para evitar cálculos processamentos desnecessários dentro da render, melhorando performance
    int column, row;
    int pixelPosition;
    float r,g,b;
    float rFactor,gFactor,bFactor;
    float luminance;
    int rowCounter, rowIncrementer;
    int columnCounter, columnIncrementer;
    int rowPadding;
    int bytesPerRow;

    /**
     * Construtor de cópia da classe Image.
     * @param _image Referência para a imagem a ser copiada.
     * @param _x Posição x da nova imagem.
     * @param _y Posição y da nova imagem.
     */
    Image(Image *_image, int _x, int _y) {
        x = _x;
        y = _y;
        selected = _image->selected;
        bmp = _image->bmp;
        rSelected = _image->rSelected;
        gSelected = _image->gSelected;
        bSelected = _image->bSelected;
        lSelected = _image->lSelected;
        lightness = _image->lightness;
        transparency = _image->transparency;
        flippedHorizontally = _image->flippedHorizontally;
        flippedVertically = _image->flippedVertically;
        setupImageInversionVariables();

        rowPadding = bmp->getRowPadding();
        bytesPerRow = bmp->getWidth() * 3 + rowPadding;
    }

    /**
     * Construtor da classe Image.
     * @param _bmp Ponteiro para o objeto Bmp contendo os dados da imagem.
     * @param _x Posição x da imagem.
     * @param _y Posição y da imagem.
     */
    Image(Bmp *_bmp, int _x, int _y) {
        x = _x;
        y = _y;
        selected = false;
        bmp = _bmp;
        rSelected = true;
        gSelected = true;
        bSelected = true;
        lSelected = false;
        lightness = 0;
        transparency = false;
        flippedHorizontally = false;
        flippedVertically = false;
        setupImageInversionVariables();
        rowPadding = bmp->getRowPadding();
        bytesPerRow = bmp->getWidth() * 3 + rowPadding;
    }

    /**
     * Construtor da classe Image com parâmetros adicionais.
     * @param _bmp Ponteiro para o objeto Bmp contendo os dados da imagem.
     * @param _x Posição x da imagem.
     * @param _y Posição y da imagem.
     * @param _rSelected Indicador de seleção do canal de cor vermelha.
     * @param _gSelected Indicador de seleção do canal de cor verde.
     * @param _bSelected Indicador de seleção do canal de cor azul.
     * @param _lSelected Indicador de seleção da luminosidade.
     * @param _flippedHorizontally Indicador de reflexão horizontal da imagem.
     * @param _flippedVertically Indicador de reflexão vertical da imagem.
     */
    Image(Bmp *_bmp, int _x, int _y, bool _rSelected, bool _gSelected, bool _bSelected, bool _lSelected, bool _flippedHorizontally, bool _flippedVertically) : bmp(_bmp), x(_x), y(_y),
                                            rSelected(_rSelected), gSelected(_gSelected), bSelected(_bSelected), lSelected(_lSelected), flippedHorizontally(_flippedHorizontally), flippedVertically(_flippedVertically) {
        selected = false;
        transparency = false;
        lightness = 0;
        setupImageInversionVariables();
        rowPadding = bmp->getRowPadding();
    }

    /**
     * Renderiza a imagem na tela.
     */
    void render() {
        if(bmp == NULL) return;

        renderImage();
        if(selected) {
            renderImageFrame();
        }
    }

    /**
    * Inicializa as variáveis auxiliares utilizadas para realizar a inversão da imagem nos eixos horizontal e vertical.
    */
    void setupImageInversionVariables() {
        if(flippedHorizontally) {
            columnCounter = bmp->getWidth();
            columnIncrementer = -1;
        } else {
            columnCounter = 0;
            columnIncrementer = 1;
        }

        if(flippedVertically) {
            rowCounter = bmp->getHeight();
            rowIncrementer = -1;
        } else {
            rowCounter = 0;
            rowIncrementer = 1;
        }
    }

    /**
    * Renderiza a imagem.
    */
    void renderImage() {
        float* data = bmp->getProcessedData();
        row = rowCounter;
        for (int i = 0; i < bmp->getHeight(); i++) {
            column = columnCounter;
            int rowOffset = i * bytesPerRow;
           for (int j = 0 ; j < bmp->getWidth(); j++) {
                pixelPosition = rowOffset + j * 3;
                r = data[pixelPosition];
                g = data[pixelPosition + 1];
                b = data[pixelPosition + 2];

                if(transparency && isWhiteRgb(r,g,b)) {
                    column += columnIncrementer;
                    continue;
                }

               if (lSelected) {
                   luminance = getLuminance(r,g,b)-lightness;
                   CV::color(luminance, luminance, luminance);
               } else {
                    rFactor = rSelected ? r-lightness : 0;
                    gFactor = gSelected ? g-lightness : 0;
                    bFactor = bSelected ? b-lightness : 0;
                    CV::color(rFactor, gFactor, bFactor);
               }

               CV::rectFill(x+column, y+row, x+column+1, y+row+1);
               column += columnIncrementer;
           }
           row += rowIncrementer;
       }
    }

    /**
     * Verifica se a cor RGB é branca (ou próxima de branca).
     * @param r Valor do canal vermelho (0 a 1).
     * @param g Valor do canal verde (0 a 1).
     * @param b Valor do canal azul (0 a 1).
     * @return true se a cor é branca, false caso contrário.
     */
    bool isWhiteRgb(float r, float g, float b) {
        return r > 0.70 && b > 0.70 && b > 0.70;
    }

    /**
     * Define a transparência da imagem.
     * @param enable true para ativar a transparência, false para desativar.
     */
    void setTransparency(bool enable) {
        transparency = enable;
    }

    /**
     * Define a luminosidade da imagem.
     * @param value O valor da luminosidade a ser definido (-1 a 1).
     */
    void setLightness(float value) {
        lightness = value;
    }

    /**
     * Obtém o valor da luminosidade atual.
     * @return O valor da luminosidade atual.
     */
    float getLightness() {
        return lightness;
    }

    /**
     * Obtém a luminância normalizada de uma cor RGB.
     * @param r Valor do canal vermelho (0 a 255).
     * @param g Valor do canal verde (0 a 255).
     * @param b Valor do canal azul (0 a 255).
     * @return O valor da luminância normalizada (0 a 1).
     */
    static float getNormalizedLuminance(unsigned char r, unsigned char g, unsigned char b) {
        return (r/ 255.0)*0.229 + (g/ 255.0)*0.587 + (b/ 255.0*0.114);
    }

    /**
     * Obtém a luminância de uma cor RGB.
     * @param r Valor do canal vermelho (0 a 1).
     * @param g Valor do canal verde (0 a 1).
     * @param b Valor do canal azul (0 a 1).
     * @return O valor da luminância.
     */
    static float getLuminance(float r, float g, float b) {
        return r*0.229 + g*0.587 + b*0.114;
    }

    /**
     * Renderiza a moldura da imagem quando selecionada.
     */
    void renderImageFrame() {
        CV::color(0,0,0);
        for(int i=0; i<frameWidth; i++) {
            CV::rect(x-i,y+i,x+bmp->getWidth()+i, y+bmp->getHeight()-i);
        }
    }

    /**
     * Verifica se o ponto (mx, my) está dentro da área ocupada pela imagem.
     * @param mx Posição x do ponto.
     * @param my Posição y do ponto.
     * @return true se o ponto está dentro da área da imagem, false caso contrário.
     */
    bool checkCollision(int mx, int my) {
      return mx >= x && mx <= (x + bmp->getWidth()) && my >= y && my <= (y + bmp->getHeight());
    }

     /**
     * Define a posição da imagem.
     * @param _x Nova posição x da imagem.
     * @param _y Nova posição y da imagem.
     */
    void setPosition(int _x, int _y) {
        x = _x;
        y = _y;
    }

    /**
     * Define se a imagem está selecionada ou não.
     * @param _selected Indicador de seleção da imagem.
     */
    void setSelected(bool _selected) {
        selected = _selected;
    }

    /**
     * Alterna o estado de seleção da imagem.
     */
    void toggleSelected() {
        selected = !selected;
    }

    /**
     * Obtém o objeto Bmp associado à imagem.
     * @return Ponteiro para o objeto Bmp.
     */
    Bmp* getBmp() {
        return bmp;
    }

    /**
     * Verifica se a imagem está selecionada.
     * @return true se a imagem está selecionada, false caso contrário.
     */
    bool isSelected() {
        return selected;
    }

    /**
     * Obtém a largura da imagem.
     * @return A largura da imagem.
     */
    int getWidth() {
        return bmp->getWidth();
    }

    /**
     * Obtém a altura da imagem.
     * @return A altura da imagem.
     */
    int getHeight() {
        return bmp->getHeight();
    }

    /**
     * Inverte a imagem horizontalmente.
     */
    void flipHorizontally() {
        flippedHorizontally = !flippedHorizontally;
        setupImageInversionVariables();
    }

    /**
     * Inverte a imagem verticalmente.
     */
    void flipVertically() {
        flippedVertically = !flippedVertically;
        setupImageInversionVariables();
    }
};


#endif // IMAGE_H_INCLUDED
