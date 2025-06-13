//Projetil.h
#pragma once
#include "BibSistema.h"

class Projetil {
    private:
        GLfloat posicao[2];
        GLfloat velocidade;
        GLint direcao; // 0: direita, 1: cima, 2: esquerda, 3: baixo
        GLboolean donoProjetil; // Indica se o projétil é do jogador (true) ou inimigo (false)

    public:
        Projetil(GLfloat x, GLfloat y, GLint d, GLboolean dono);
        GLvoid corpoProjetil();
        GLvoid desenhaProjetil();
        GLboolean moveProjetil();
        GLfloat* getPosicaoProjetil();
        GLboolean verificaColisao(GLfloat* posicaoInimigo, GLfloat* tamanhoInimigo);
        ~Projetil();
};