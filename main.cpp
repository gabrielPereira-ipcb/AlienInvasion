//main.cpp
#include "BibSistema.h"
#include "NaveJogador.h"

using namespace std;// Usar o namespace std para evitar escrever std:: antes de cada função da biblioteca padrão

/*----Funcoes auxiliares----*/
GLvoid criarNaveJogador(); //funcao auxliar 
GLvoid criarNavesInimigo(); //funcao auxiliar


/*----Funcoes referentes ao estado de jogo----*/
GLvoid desenhaEcraJogo(GLvoid); //funcao auxiliar para desenhar o ecra do jogo
GLvoid desenhaUIJogo(GLvoid); //funcao auxiliar para desenho da UI do jogo
GLvoid idleJogo(GLvoid); //funcao auxiliar para o idle do jogo. 
GLvoid tecladoJogo(unsigned char tecla, int x, int y); //funcao auxiliar para o teclado do jogo


/*----funcoes para o estado inicial----*/
GLvoid desenhaUIEcraInicial(GLvoid); //funcao auxiliar para desenhar a UI do menu inicial
GLvoid desenhaEcraInicial(GLvoid); //funcao para desenhar o ecra inicial do jogo. Por que ter uma funcao para desenhar a UI e uma para desenhar o ecra inicial?
GLvoid idleEcraInicial(GLvoid); //funcao auxiliar para o idle do ecra inicial
GLvoid tecladoEcraInicial (unsigned char tecla, int x, int y); 

GLvoid desenhaUIEcraSuporte(GLvoid);
GLvoid desenhaEcraSuporte(GLvoid);
GLvoid idleEcraSuporte(GLvoid);
GLvoid tecladoSuporte(unsigned char tecla, int x, int y);



/*----funcoes para o estado de pausa -----*/
GLvoid desenhaUIEcraPausa(GLvoid);
GLvoid desenhaEcraPausa(GLvoid);
GLvoid idleEcraPausa(GLvoid);
GLvoid tecladoPausa(unsigned char tecla, int x, int y);


/*----funcoes para o estado de gameOver----*/
GLvoid desenhaUIGameOver(GLvoid);
GLvoid desenhaEcraGameOver(GLvoid);
GLvoid idleEcraGameOver(GLvoid);
GLvoid tecladoGameOver(unsigned char tecla,int x,int y);



/*----temporizador----*/

/*----fim temporizador----*/

/*----variaveis globais externas----*/

GLfloat tamanhoMundo = 20.0f;
GLfloat coordenadasMundo[4] =  {-tamanhoMundo, tamanhoMundo, -tamanhoMundo, tamanhoMundo}; //As coordenadas do mundo são: xmin, xmax, ymin, ymax. Ou seja, duma ponta a outra do mundo, no eixo x e no eixo y, tem 2 vezes o tamanhoMundo
GLfloat naveJogadorTamanho = 2.0f;


int larguraEcra = 720, alturaEcra = 720;

enum EstadoJogo {
    INICIAL,
    PAUSADO,
    JOGANDO,
    AJUDAPAUSA,
    AJUDAINICIAL,
    GAMEWIN,
    GAMEOVER
};

EstadoJogo estadoAtual = INICIAL;

NaveJogador* naveJogador; // ponteiro para a nave do jogador

/*----Funcoes do ecra inicial----*/
GLvoid desenhaUIEcraInicial(){
    stringstream buffer;
    char caracter;

    glColor3f(0.0f, 1.0f, 0.0f); // cor verde para o texto, mesma cor que a nave amiga

    buffer.str(""); // string vazia
    buffer.clear(); // limpa o estado de erro
    buffer << "ALIEN INVASION"<<endl; // titulo do jogo
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)+10.0f, 0.0f); //posiciona o texto no centro do ecra

    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, caracter); //Desenha cada carcter do titulo
    }

    glColor3f(1.0f,1.0f,1.0f);
    buffer.str(""); // string vazia
    buffer.clear(); // limpa o estado de erro
    buffer << "Press ENTER to play"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f), 0.0f); 

    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter); //Desenha cada carcter 
    }

    glColor3f(1.0f,1.0f,1.0f);
    buffer.str(""); // string vazia
    buffer.clear(); // limpa o estado de erro
    buffer << "Press H for help"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-5.0f, 0.0f);

    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter); //Desenha cada carcter 
    }

    glColor3f(1.0f,1.0f,1.0f);
    buffer.str(""); // string vazia
    buffer.clear(); // limpa o estado de erro
    buffer << "Press ESC to exit"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-10.0f, 0.0f); 

    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter); //Desenha cada carcter 
    }
}

GLvoid desenhaEcraInicial(GLvoid){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Define a cor de fundo como preta
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
     
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);

    glMatrixMode(GL_MODELVIEW); // Definir o modo da matriz como modelview
    glLoadIdentity();

    desenhaUIEcraInicial(); // Desenha a UI do ecra inicial

    glutSwapBuffers();
}

GLvoid idleEcraInicial(GLvoid){
    
}

GLvoid tecladoEcraInicial(unsigned char tecla, int x,int y){
    switch (tecla) {
    

    case 13: // "ENTER"
        
        glutDisplayFunc(desenhaEcraJogo); // Muda a função de desenho para o jogo
        glutKeyboardFunc(tecladoJogo); // Muda a função de teclado para o jogo
        glutIdleFunc(idleJogo); // Muda a função idle para o jogo

        criarNaveJogador(); // Cria a nave do jogador

        glutPostRedisplay(); // Redesenha a cena
        break;

    case 'h': // "Help :)"
    case 'H':
        glutDisplayFunc(desenhaEcraSuporte);
        glutIdleFunc(idleEcraSuporte);
        glutKeyboardFunc(tecladoSuporte);
        glutPostRedisplay(); // Redesenha a cena
        estadoAtual = AJUDAINICIAL; // Muda o estado atual para AJUDA
        std::cout << "Indo para a tela de ajuda..." << std::endl;
        std::cout << estadoAtual << std::endl;

        break;

    case 27:
     // "ESC"
    exit(0); // Sair do jogo
    break;
    }
}

/*----funcoes de suporte do jogo----*/
GLvoid desenhaUIEcraSuporte(GLvoid){
    stringstream buffer;
    char caracter;

    glColor3f(0.0f, 1.0f, 0.0f); 
    buffer.str("");
    buffer.clear();
    buffer << "GAME HELP"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)+10.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, caracter);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer<<"W, S, A, D - Move the ship in cardinal directions"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-15.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f), 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer<<"Q, E - Rotate the ship in 90 degree angles"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-15.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-1.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer<<"Space - Shoot"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-15.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-2.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer<<"Press B to go back"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-5.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }
}
GLvoid desenhaEcraSuporte(GLvoid){
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaUIEcraSuporte();

    glutSwapBuffers();


}
GLvoid idleEcraSuporte(GLvoid){
    //TODO
}
GLvoid tecladoSuporte(unsigned char tecla, int x, int y){
    switch (tecla)
    {
    case 'b':
    case 'B':
        //depende qual era o ultimo estado. Se era o pausa, volta ao estado de pausa, se era o ecra inicial, volta ao ecra inicial
        std::cout << "Estado atual: " << (estadoAtual == AJUDAPAUSA ? "AJUDAPAUSA" : "AJUDAINICIAL") << std::endl;
        
        if (estadoAtual == AJUDAPAUSA) 
        {
            glutDisplayFunc(desenhaEcraPausa);
            glutKeyboardFunc(tecladoPausa);
            glutIdleFunc(idleEcraPausa);
            estadoAtual = PAUSADO;
            glutPostRedisplay();
        }
        else if (estadoAtual == AJUDAINICIAL)
        {
            glutDisplayFunc(desenhaEcraInicial);
            glutKeyboardFunc(tecladoEcraInicial);
            glutIdleFunc(idleEcraInicial);
            estadoAtual = INICIAL;
            glutPostRedisplay();
        }
        break;
    
    default:
        break;
    }
}

/*----Funcoes de pausa----*/
GLvoid desenhaUIEcraPausa(GLvoid){
    stringstream buffer;
    char caracter;

    glColor3f(0.0f, 1.0f, 0.0f); 
    buffer.str("");
    buffer.clear();
    buffer << "GAME PAUSED"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)+10.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, caracter);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer << "Press ENTER to continue"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f), 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer << "Press M to return to menu"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-5.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    buffer.str("");
    buffer.clear();
    buffer << "Press H for help"<<endl;
    glRasterPos3f(coordenadasMundo[0]+((coordenadasMundo[1]-coordenadasMundo[0])/2.0f)-3.0f, coordenadasMundo[2] + ((coordenadasMundo[3]-coordenadasMundo[2])/2.0f)-10.0f, 0.0f);
    while (buffer.get(caracter)){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, caracter);
    }
}

GLvoid desenhaEcraPausa(GLvoid){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
     
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaUIEcraPausa();

    glutSwapBuffers();
}

GLvoid idleEcraPausa(GLvoid){
    // Não é necessário fazer nada no idle da pausa
}

GLvoid tecladoPausa(unsigned char tecla, int x, int y){
    switch (tecla) {
        case 13: //Enter
        
            // Volta para o jogo
            glutDisplayFunc(desenhaEcraJogo);
            glutKeyboardFunc(tecladoJogo);
            glutIdleFunc(idleJogo);
            estadoAtual = JOGANDO;
            glutPostRedisplay();
            break;

        case 'm':
        case 'M':
            // Volta para o menu inicial
            glutDisplayFunc(desenhaEcraInicial);
            glutKeyboardFunc(tecladoEcraInicial);
            glutIdleFunc(idleEcraInicial);
            estadoAtual = INICIAL;
            glutPostRedisplay();
            break;

        case 'h':
        case 'H':
            // Vai para a tela de ajuda
            glutDisplayFunc(desenhaEcraSuporte);
            glutIdleFunc(idleEcraSuporte);
            glutKeyboardFunc(tecladoSuporte);
            estadoAtual = AJUDAPAUSA;
            glutPostRedisplay();
            break;
    }
}

/*----Funcoes GameOver----*/
GLvoid desenhaUIGameOver(GLvoid){
    //TODO
}
GLvoid desenhaEcraGameOver(GLvoid){
    //TODO
}
GLvoid idleEcraGameOver(GLvoid){
    //TODO
}
GLvoid tecladoGameOver(unsigned char tecla, int x, int y){
    //TODO
}

/*----funcao cria nave jogador----*/
GLvoid criarNaveJogador(){
    naveJogador = new NaveJogador(); // Cria a nave do jogador usando seu costrutor default

}

/*----fim funcao cria nave jogador----*/

/*----funcao cria inimigos----*/

/*----fim funcao cria inimigos----*/

/*----funcoes do jogo----*/


/*----fim funcoes do jogo----*/

GLvoid desenhaEcraJogo(GLvoid) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Define a cor de fundo como preta
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
     
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);

    glMatrixMode(GL_MODELVIEW); // Definir o modo da matriz como modelview
    glLoadIdentity();

    /*----desenhar objetos na cena (nave Amiga etc)----*/
    if (naveJogador) {
        std::cout << "Posição da nave: X=" << naveJogador->getPosicao()[0] << ", Y=" << naveJogador->getPosicao()[1]<< "\t Angulo de ataque na nave: "<< naveJogador->getAnguloRotacao() +90.0f << std::endl;
        naveJogador->desenha(); // Desenha a nave do jogador
    } else {
        std::cerr << "Erro: Nave do jogador não foi criada!" << std::endl;
    }

    /*----desenhar a nave do jogador----*/


    
    //Renderizar todos os inimigos
    

    //Renderizar todas as balas do jogador

    //Renderizar todas as balas do inimgio

    glutSwapBuffers();
}

GLvoid idleJogo (GLvoid){

}

/*---- funcao de rechape ecra ----
GLvoid rechapeEcra(GLint largura, GLint altura){
    glViewport(0,0,largura,altura); // Define a viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]); // Define a projecao ortogonal
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
*/

GLvoid tecladoJogo(unsigned char tecla, int x, int y) {
    GLboolean move = false;
    GLboolean rotaciona = false;

    switch (tecla) {
    case 27: // "ESC"
        // Pausa o jogo
        glutDisplayFunc(desenhaEcraPausa);
        glutKeyboardFunc(tecladoPausa);
        glutIdleFunc(idleEcraPausa);
        estadoAtual = PAUSADO;
        glutPostRedisplay();
        break;

    case 'w':
    case 'W': //vai para cima
        move = naveJogador->moverNave(2); 
        break;

    case 'a':
    case 'A': //vai para esquerda
        move = naveJogador->moverNave(1);
        break;

    case 's':
    case 'S': //vai para baixo
        move = naveJogador->moverNave(3);
        break;

    case 'd':
    case 'D': //vai para direita
        move = naveJogador->moverNave(0);
        break;
    case 'q':
    case 'Q': //roda 90graus "esquerda" "anti-horario"
        rotaciona = naveJogador->rodarNave(1);
        break;
    case 'e':
    case 'E': //roda -90graus "direita" "horario"
        rotaciona = naveJogador->rodarNave(0);
        break;
    }
    

    //se a nave se mexeu ou rotacionou é preciso redesenhar
    if (move || rotaciona) {
        if (move) {
            std::cout << "Nave movida!" << std::endl;
        }
        if (rotaciona) {
            std::cout << "Nave rotacionada!" << std::endl;
        }
        glutPostRedisplay(); // Redesenha a cena
    } else {
        std::cout << "Ação inválida!" << std::endl;
    }
}


//#### funcao ecra inicial ####

//#### funcao pausa do jogo ####

//#### funcao game over ####

//#### funcao ganha jogo ####


/*----funcao suporte do jogo----*/ 





/*----fim funcao suporte do jogo----*/

int main (int argc, char*argv[]){
    glutInit(&argc, argv); 

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowPosition(0, 0); //definir a posição inicial da janela de renderização no ecrã. (x,y) é o ponto de origem da janela. (0,0) é o canto superior esquerdo do ecrã, ou seja, a janela será aberta no canto superior esquerdo do ecrã.
    glutInitWindowSize(larguraEcra, alturaEcra);  //define o tamanho da janela 
    
    glutCreateWindow("Alien Invasion"); 
    


    glutDisplayFunc(desenhaEcraInicial);
    glutIdleFunc(idleEcraInicial);
    glutKeyboardFunc(tecladoEcraInicial); 


    glutMainLoop();//Inicia o ciclo de eventos que permite detetar eventos

    return 0;
}