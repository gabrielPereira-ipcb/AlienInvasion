//NaveJogador.h
#pragma once
#include "BibSistema.h"

extern GLfloat NaveJogadorTamanho;

class NaveJogador{
    //variaveis privadas
    private:
        GLfloat posicao [2]; // Posição da nave no mundo
        GLfloat velocidade; 
        GLfloat anguloRotacao; //Angulo de rotacao da nave. pode ser +ou- 90 graus, a depender da orientacao


        GLvoid desenhaNaveJogador(GLvoid); // Método privado para desenhar a nave do jogador que é composto por apenas um triangulo verde

    //variaveis publicas
    public:
        //construtor default
        NaveJogador();

        //construtor com parametros
        NaveJogador(GLfloat, GLfloat, GLint);

        GLvoid desenha(GLvoid); //metodo publico para desenhar a nave do jogador
        GLboolean moverNave(GLint); // metodo publico para mover a nave do jogador
        GLboolean rodarNave (GLint); //metodo para rodar a nave

        
        /*getters*/
        GLfloat* getPosicao();//ponteiro para o valor da posicao
        GLfloat getAnguloRotacao(); // Retorna o ângulo de rotação da nave

        /*setters*/
        
        
        /*destrutor*/ 
        ~NaveJogador();


};