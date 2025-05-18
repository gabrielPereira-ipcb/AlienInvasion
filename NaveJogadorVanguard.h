// NaveJogadorVanguard.h.h
#pragma once
#include "BibSistema.h" // Includes standard libs and OpenGL/freeGLUT



class NaveJogadorVanguard {
    private:
        GLfloat posicao [2]; // Posição da nave no mundo
        GLfloat velocidade; 

        GLvoid cockpit(GLvoid); // Método privado para desenhar a nave
        GLvoid canhao(GLvoid); // Método privado para desenhar o canhão da nave

    public:
        //construtor default
        NaveJogadorVanguard();

        //construtor com parametros
        NaveJogadorVanguard(GLfloat, GLfloat);

        //metodos de desenho
        GLvoid desenha(GLvoid); //desenha a nave
        GLboolean moverNaveJogador(GLint);
        GLfloat* getPosicao();
    
        ~NaveJogadorVanguard();    //destrutor

};
