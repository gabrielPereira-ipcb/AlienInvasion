#include "NaveJogadorVanguard.h" 

/*A NaveJogadorVanguard é a nave padrão do jogador. No jogo há uma segunda nave que o jogador poder jogar, mas esta é um upgrade.
  A NaveJogadorVanguard padrão é composta por:
    1. Canhao - que tambem engloba as assas, na cor azul
    2. cockpit - um quadradro verde
  */

NaveJogadorVanguard::NaveJogadorVanguard() {
    posicao[0] = 0.0f; // Define a posição X da nave
    posicao[1] = coordenadasMundo[2]+2.0f; // Define a posição Y da nave um pouco acima do limite inferior do mundo
    velocidade = 1.0f; 
    
}

NaveJogadorVanguard::NaveJogadorVanguard(GLfloat x, GLfloat y){
    posicao[0] = x;
    posicao[1] = y;

    velocidade = 1.0f;

}

GLvoid NaveJogadorVanguard::cockpit(GLvoid){
    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o cockpit

    glBegin(GL_QUADS);{
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0, naveJogadorTamanho);
        glVertex2f(naveJogadorTamanho, naveJogadorTamanho);
        glVertex2f(naveJogadorTamanho, 0.0f);
    }glEnd();
}

GLvoid NaveJogadorVanguard::canhao(GLvoid){
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o canhão

    glBegin(GL_TRIANGLES);{
        glVertex2f(0.0f, 0.0f);
        glVertex2f(naveJogadorTamanho*2, 0.0f);
        glVertex2f(naveJogadorTamanho, naveJogadorTamanho*2);
    }glEnd();
}

GLvoid NaveJogadorVanguard::desenha(GLvoid){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPushMatrix();
    glTranslatef(posicao[0]- naveJogadorTamanho, posicao[1], 0.0f); // Translada a nave para a posição correta.. O canhão é desenhado na posição (0,0)
    canhao(); // Desenha o canhão
    glPopMatrix();



    glPushMatrix();
    glTranslatef(posicao[0] - naveJogadorTamanho/2, posicao[1], 0.0f); // Translada a nave para a posição correta
    // O cockpit é desenhado na posição (0,1/4) para que fique centralizado em relação ao canhão **sendo a variavel naveJogadorTamanho o tamanho do lado do quadrado que representa o cockpit**
    // 1/4 quando naveJogadorTamanho = 1.0f
    // O canhão é desenhado na posição (0,0) para que fique centralizado em relação ao cockpit

    cockpit(); // Desenha o cockpit
    glPopMatrix();

    

    /*----TODO: explicar o que vem a seguinr----*/
    
    glPushMatrix();
    glPopMatrix();

    glPopMatrix();
}

GLboolean NaveJogadorVanguard::moverNaveJogador(GLint direcao){
    GLboolean move = false;

    switch (direcao) {
    case 0: //direita
        if (posicao[0] < coordenadasMundo[1] - naveJogadorTamanho) {
            posicao[0] += velocidade;
            move = true;
        }
        break;
    case 1: //esquerda
        if (posicao[0] > coordenadasMundo[0] + naveJogadorTamanho) {
            posicao[0] -= velocidade;
            move = true;
        }
        break;
    case 2: //cima
        // A altura do canhao : o tamanho da altura do canhao é o dobro da sua base
        if (posicao[1] < coordenadasMundo[3] - naveJogadorTamanho*2) {
            posicao[1] += velocidade;
            move = true;
        }
        break;
    case 3: //baixo
        if (posicao[1] > coordenadasMundo[2]+ naveJogadorTamanho) {
            posicao[1] -= velocidade;
            move = true;
        }
        break;
    default:
        std::cerr << "Direção inválida!" << std::endl;
        break;
    }
    return move;
}

GLfloat* NaveJogadorVanguard::getPosicao(){
    return posicao;
}

NaveJogadorVanguard::~NaveJogadorVanguard() {
    // Destroi a nave do jogador
    std::cout << "Destruindo a nave do jogador!" << std::endl;
}