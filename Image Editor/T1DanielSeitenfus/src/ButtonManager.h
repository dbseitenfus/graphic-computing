#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <vector>
#include "Botao.h"

class ButtonManager {

public:
    std::vector<Botao*> vet_botao;
    Manager() {
        vet_botao = {};
    }

    void addBotao(int x, int y, int larg, int alt, char* text) {
        vet_botao.push_back(new Botao(x, y, larg, alt, text));
    }

    void Render() {
        for(int i=0; i<vet_botao.size(); i++) {
            vet_botao[i]->Render();
        }
    }

    void clique(int mx, int my) {
        for(int i=0; i<vet_botao.size(); i++) {
            if(vet_botao[i]->Colidiu(mx, my)) {
                vet_botao[i]->executa();
            }
        }
    }



};


#endif // MANAGER_H_INCLUDED
