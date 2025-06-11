//naveJogador.cpp
#include "NaveJogador.h"


/*----Nave padrao do jogador----*/

/*----construtor default----*/
NaveJogador::NaveJogador(){
    posicao[0] = 0.0f;
    posicao[1] = coordenadasMundo[2]+2.0f;//defina a posicao y inicial um pouco acima do limite inferior do mundo
    anguloRotacao = 0.0f; //90 é orientado para cima. Segue a convecao trigonometrica Leste=0, Norte =90, Oeste = 180 e Sul =270. Entretanto, como a nave já é criado com a ponta para o norte, o seu angulo inicial é 0.
    velocidade = 1.0f;
}

/*----construtor com parametros----*/
NaveJogador::NaveJogador(GLfloat x, GLfloat y, GLint angulo){
    posicao[0] = x;
    posicao[1] = y;
    anguloRotacao = angulo;
    velocidade = 1.0f;
}

/*----metodo para desenhar a nave do jogador----*/
GLvoid NaveJogador::desenhaNaveJogador(GLvoid){
    glColor3f(0.0f, 1.0f, 0.0f); //cor verde para a cor da nave amiga
    glBegin(GL_TRIANGLES);{
        // Vértices centralizados na origem, com a ponta para cima
        glVertex2f(-naveJogadorTamanho/2, -naveJogadorTamanho/2); // Base esquerda
        glVertex2f(naveJogadorTamanho/2, -naveJogadorTamanho/2);  // Base direita
        glVertex2f(0.0f, naveJogadorTamanho/2);                   // Ponta para cima
    }
    glEnd();
}

/*----metodo para desenhar a nave do jogador----*/
GLvoid NaveJogador::desenha(GLvoid){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    // Primeiro translada para a posição
    glTranslatef(posicao[0], posicao[1], 0.0f);
    // Depois rotaciona em torno do ponto de origem da nave
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);
    
    desenhaNaveJogador();
    glPopMatrix();
}

/*----metodo para mover a nave do jogador----*/
GLboolean NaveJogador::moverNave(GLint direcao){
    GLboolean move = false;

    switch (direcao) {
        /*Foi necessario adicionar uma logica que bloqueia a nave do jogador sair do ecra*/
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

/*----Metodo para rodar a nave----*/
GLboolean NaveJogador::rodarNave(GLint direcao){
    GLboolean rotaciona = false;

    /*Nao ha limite de rotacao. */
    switch (direcao){
        case 1: //"esquerda" somar 90graus
            anguloRotacao += 90.0f;
            rotaciona = true;
            break;
        case 0: //"direita" subtrarir 90graus
            anguloRotacao -= 90.0f;
            rotaciona = true;
        default:
            std::cerr<<"Rotação inválida"<<std::endl;
            break;
    }
    return rotaciona;
}

GLfloat* NaveJogador::getPosicao(){
    return posicao;
}

GLfloat NaveJogador::getAnguloRotacao(){
    return anguloRotacao;
}

NaveJogador::~NaveJogador() { //destrutor da nave do Jogador
    // Destroi a nave do jogador
    std::cout << "Destruindo a nave do jogador!" << std::endl;
}