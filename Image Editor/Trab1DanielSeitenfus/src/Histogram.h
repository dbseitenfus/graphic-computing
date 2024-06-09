#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
#include "gl_canvas2d.h"
#include "Bmp.h"
using namespace std;

/**
 * @file Histogram.h
 * @brief Definição da classe Histogram, que representa um histograma de uma imagem.
 */

/**
 * Modos de visualização do histograma. O gráfico pode estar "preenchido" ou "vazado", permitindo diferentes visões.
 */
enum class HistogramVisualMode {
    FILLED = 0,
    UNFILLED
};

HistogramVisualMode visualMode;

/**
 * Classe que representa um histograma de uma imagem.
 */
class Histogram {
    int height, width;
    float xIncrementer;
    Image *image;

    vector<int> rVector;
    vector<int> gVector;
    vector<int> bVector;
    vector<int> lVector;

    //Variáveis auxiliares para renderização.
    const int NUM_COLORS = 256;
    int bytesPerRow;
    int rowPadding;
    float lightness;

public:
    int x1=0, y1=0, x2=200, y2=200;

    Histogram(int _x1, int _y1, int _x2, int _y2, Image *_image) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), image(_image) {
        width = x2-x1;
        height = y2-y1;
        xIncrementer = width/NUM_COLORS;
        visualMode = HistogramVisualMode::FILLED;
        setupVariables();
        generateRGBVectors();
    }

    Histogram(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
        width = x2-x1;
        height = y2-y1;
        xIncrementer = width/NUM_COLORS;
        visualMode = HistogramVisualMode::FILLED;
        for (int i=0; i<NUM_COLORS; i++) {
            rVector.push_back(0);
            bVector.push_back(0);
            gVector.push_back(0);
            lVector.push_back(0);
        }
    }

    /**
    * Inicializa variáveis auxiliares da classe.
    */
    void setupVariables() {
        rowPadding = image->getBmp()->getRowPadding();
        bytesPerRow = image->getBmp()->getWidth() * 3 + rowPadding;
        lightness = image->getLightness()*(NUM_COLORS-1);
    }

    /**
     * Altera o modo de visualização do histograma.
     */
    static void changeVisualizationOption() {
        visualMode = visualMode == HistogramVisualMode::FILLED ? HistogramVisualMode::UNFILLED : HistogramVisualMode::FILLED;
    }

    /**
     *  Renderiza o histograma na tela.
     */
    void render() {
        CV::color(0,0,0);
        CV::rect(x1, y1, x2, y2);

        renderHistogramColumns(rVector, Color::RED);
        renderHistogramColumns(gVector, Color::GREEN);
        renderHistogramColumns(bVector, Color::BLUE);
        renderHistogramColumns(lVector, Color::GREY);
    }

    /**
     * Renderiza as colunas do histograma.
     * @param dataVector Vetor de valores de dados para as colunas.
     * @param color Cor da coluna.
     */
    void renderHistogramColumns(std::vector<int> dataVector, Color color) {
        if(dataVector.empty()) return;

        CV::color(color.r,color.g,color.b);

        int x1PreviousPoint = x1, y1PreviousPoint = y1;
        float lineX = 0;

        calculateHighestValue(dataVector);
        if(highest == 0) return;

        for(int i=0; i<NUM_COLORS; i++) {
            int lineY = getHistogramLineHeight(dataVector[i]);
            if(visualMode == HistogramVisualMode::FILLED) {
               CV::line(x1+lineX, y1, x1+lineX, y1+lineY);
            } else if (visualMode == HistogramVisualMode::UNFILLED) {
                CV::line(x1PreviousPoint, y1PreviousPoint, x1+lineX, y1+lineY);
                x1PreviousPoint = x1+lineX;
                y1PreviousPoint = y1+lineY;
            }
            lineX += xIncrementer;
        }
    }

     /**
     * @brief Obtém a altura de uma linha do histograma com base em seu valor.
     * @param lineValue Valor da linha.
     * @return Altura da linha.
     */
    int getHistogramLineHeight(int lineValue) {
        return height*lineValue/highest;
    }


   /**
     * Define a imagem associada ao histograma.
     * @param _image Ponteiro para a imagem.
     */
    void setImage(Image *_image) {
        image = _image;
        setupVariables();
        generateRGBVectors();
    }

private:
    int highest = 0; /**< Valor mais alto do histograma */

    /**
     * Calcula o valor mais alto do histograma.
     * @param vetor Vetor com os valores do histograma.
     */
    void calculateHighestValue(const std::vector<int>& vetor) {
        if (vetor.empty()) return;

        for (int value : vetor) {
            highest = max(highest, value);
        }
    }

    /**
     * @brief Gera os vetores de RGB e luminância para a imagem associada.
     */
    void generateRGBVectors() {
        clearVectors();
        if(image == nullptr || image->getBmp() == nullptr) return;

        Bmp *bitmap = image->getBmp();
        uchar* data = bitmap->getImage();

        for (int i = 0; i < bitmap->getHeight(); i++) {
            int rowOffset = i * bytesPerRow;
           for (int j = 0; j < bitmap->getWidth(); j++) {
               int pixelPosition = rowOffset + j * 3;
               unsigned char r = data[pixelPosition];
               unsigned char g = data[pixelPosition + 1];
               unsigned char b = data[pixelPosition + 2];

                if(image->rSelected) {
                    int value = r-lightness;
                    if(isInRgbRange(value))rVector[value]++;
               }

               if(image->gSelected) {
                    int value = g-lightness;
                    if(isInRgbRange(value))gVector[value]++;
               }

               if(image->bSelected) {
                    int value = b-lightness;
                    if(isInRgbRange(value))bVector[value]++;
               }

               if (image->lSelected) {
                   float luminance = Image::getLuminance(r,g,b)-lightness;
                   if(isInRgbRange(luminance)) lVector[luminance]++;
               }
           }
       }
    }

    /**
     * Verifica se um valor está dentro do intervalo RGB válido.
     * @param value Valor a ser verificado.
     * @return true se o valor estiver dentro do intervalo válido, false caso contrário.
     */
    bool isInRgbRange(int value) {
        return value > 0 && value < NUM_COLORS;
    }

    /**
     * Limpa/inicializa os vetores do histograma.
     */
    void clearVectors() {
        highest = 0;
        clearVector(rVector);
        clearVector(gVector);
        clearVector(bVector);
        clearVector(lVector);
    }

    /**
     * Limpa um vetor e o preenche com zeros.
     * @param vetor Vetor a ser limpo.
     */
    void clearVector(std::vector<int>& vetor) {
        vetor.assign(NUM_COLORS, 0);
    }
};


#endif // HISTOGRAM_H_INCLUDED
