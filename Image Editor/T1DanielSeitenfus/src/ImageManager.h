#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <vector>
using namespace std;
#define NO_IMAGE_SELECTED -1

class ImageManager {

    std::vector<Image*> images;
    int selectedImageIndex = NO_IMAGE_SELECTED;
    bool draggingImage = false;
    //int draggedImagePivotX = -1, draggedImagePivotY = -1;

public:
    ImageManager() {
        images = {};
    }

    void addImage(Image *image) {
        images.push_back(image);
    }

    void convertBGRtoRGB() {
        for(int i=0; i<images.size(); i++) {
            images[i]->getBmp()->convertBGRtoRGB();
        }
    }

    void render() {
        for(int i=0; i<images.size(); i++) {
            images[i]->render();
        }
    }

    bool hasImageSelected() {
        return selectedImageIndex >= 0;
    }

    void updateSelectedImagePosition(int mx, int my) {
        if(draggingImage){
            images[selectedImageIndex]->setPosition(mx, my);
            /*int x = images[draggedImageIndex]->getX();
            int y = images[draggedImageIndex]->getY();
            images[draggedImageIndex]->setPosition(mx-x, my-y);

            images[draggedImageIndex]->setPosition(mx-draggedImagePivotX, my-draggedImagePivotY);
            cout << "x " << mx-draggedImagePivotX << ", y: " << my-draggedImagePivotY << endl;*/
        }
    }


    void onMouseUpdated(int mx, int my, int state) {
        if(state == 0) {
            for(int i=0; i<images.size(); i++) {
                /*
                    H� 3 cen�rios que podem ocorrer a partir da detec��o de colis�o em clique:
                    1 - Clique sem nenhum imagem selecionada anteriormente -> Seleciona a imagem clicada
                    2 - Clique na imagem j� selecionada -> Retira a sele��o da imagem j� selecionada //TODO: Implementar a verifica��o se h� dragging aqui. Se h�, n�o deve retirar a sele��o, pois o usu�rio n�o quer descelecionar a imagem, e sim, apenas arrast�-la.
                    3 - Clique em imagem n�o-selecionada com outra imagem j� selecionada -> Retirar a sele��o da imagem anterior e aplicar sele��o na imagem clicada
                */
                if(images[i]->checkCollision(mx, my)) {
                    if(selectedImageIndex == NO_IMAGE_SELECTED) {
                        images[i]->toggleSelected();
                        selectedImageIndex = i;
                        draggingImage = true;
                        setRenderPriority(i);
                    } else if(i == selectedImageIndex) {
                        images[i]->toggleSelected();
                        selectedImageIndex = NO_IMAGE_SELECTED;
                    } else if(hasImageSelected() && i != selectedImageIndex) {
                        images[selectedImageIndex]->toggleSelected();
                        images[i]->toggleSelected();
                        selectedImageIndex = i;
                        draggingImage = true;
                        setRenderPriority(i);
                    }
                }
            }
        }else if(state == 1) {
            draggingImage = false;
        }

        updateSelectedImagePosition(mx , my);
    }

    void setRenderPriority(int index) {
        Image *image = images[index];
        images.erase(images.begin() + index);
        images.push_back(image);
    }

    Image* getSelectedImage() {
        if(!hasImageSelected()) {
            return NULL;
        }

        return images[selectedImageIndex];
    }

};


#endif // IMAGEMANAGER_H_INCLUDED
