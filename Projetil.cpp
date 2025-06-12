//Projetil.cpp
#include "Projetil.h"

Projetil::Projetil(GLfloat x, GLfloat y, GLint d, GLboolean dono) {
    posicao[0] = x;
    posicao[1] = y;
    velocidade = 2.0f; // Velocidade do projétil
    direcao = d; // Direção inicial (cima)
    

    donoProjetil = dono; // Define se o projétil é do jogador ou inimigo
}

GLvoid Projetil::desenhaProjetil() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    // Primeiro translada para a posição
    glTranslatef(posicao[0], posicao[1], 0.0f);
    // Aplica a escala
    glScalef(escala, escala, 1.0f);
    // Rotaciona baseado na direção
    glRotatef(direcao * 90.0f, 0.0f, 0.0f, 1.0f);
    
    corpoProjetil();
    glPopMatrix();
}

GLvoid Projetil::corpoProjetil() {
    if (donoProjetil) {
        glColor3f(0.0f, 0.0f, 1.0f); // azul para projéteis do jogador
    } else {
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho para projéteis inimigos
    }
    
    // Desenha um retângulo maior para ser mais visível
    glBegin(GL_QUADS);
        glVertex2f(-tamanhoProjetil, -tamanhoProjetil);
        glVertex2f(tamanhoProjetil, -tamanhoProjetil);
        glVertex2f(tamanhoProjetil, tamanhoProjetil);
        glVertex2f(-tamanhoProjetil, tamanhoProjetil);
    glEnd();
}

GLvoid Projetil::moveProjetil() {
    // Converte a direção em ângulo em radianos
    GLfloat rad = (direcao * 90.0f * M_PI) / 180.0f;
    
    // Move o projétil na direção do ângulo
    posicao[0] += velocidade * cos(rad);
    posicao[1] += velocidade * sin(rad);
}

GLfloat* Projetil::getPosicaoProjetil() {
    return posicao;
}

Projetil::~Projetil() {
    
}