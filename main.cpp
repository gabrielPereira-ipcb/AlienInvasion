// main.cpp
// Ficheiro principal do jogo Alien Invasion

// Inclusão do ficheiro de cabeçalho do sistema que contém bibliotecas e variáveis globais
#include "BibSistema.h"
#include "NaveJogadorVanguard.h"


/*----Definicoes de Funcoes ----*/
GLvoid desenhaEcraPrincipal (GLvoid); // Callback para desenhar o ecrã principal
GLvoid rechapeEcra(GLint largura, GLint altura); // Callback para redimensionar a janela
GLvoid teclado(unsigned char key, int x, int y); // Callback para teclado

/*----FIM Definicoes de Funcoes ----*/


/*----Variaveis globais----*/
GLfloat tamanhoDoMundo = 20.0f; // Tamanho do mundo
GLfloat coordenadasMundo[4] =  {-tamanhoDoMundo, tamanhoDoMundo, -tamanhoDoMundo, 20.0f}; // Coordenadas do mundo (esquerda, direita, baixo, cima)
GLfloat naveJogadorTamanho = {1.0f}; // tamanho base do quadadro da nave do jogador

NaveJogadorVanguard* naveJogador; // Ponteiro para a nave do jogador

/*----FIM Variaveis globais----*/


/*----Funcao para criar a nave do jogador----*/
GLvoid criarNaveJogador() {
    naveJogador = new NaveJogadorVanguard(coordenadasMundo[0] + ((coordenadasMundo[1] - coordenadasMundo[0]) / 2.0f), coordenadasMundo[2] + (naveJogadorTamanho) ); // Cria a nave do jogador
    if (naveJogador) {
        std::cout << "Nave do jogador criada com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao criar a nave do jogador!" << std::endl;
    }
}


GLvoid desenhaEcraPrincipal (GLvoid){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // limpa o ecra

    //Matriz identidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]); // Define a projecao ortogonal

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*----desenhar objetos na cena (nave Amiga etc)----*/

    //verifica se o ponteiro da nave do jogador é valido
    if (naveJogador) {
        std::cout << "Posição da nave: X=" << naveJogador->getPosicao()[0] << ", Y=" << naveJogador->getPosicao()[1] << std::endl;
        naveJogador->desenha(); // Desenha a nave do jogador
    } else {
        std::cerr << "Erro: Nave do jogador não foi criada!" << std::endl;
    }
    // Aqui pode-se desenhar outros objetos, como inimigos, balas, etc.

    /*----FIM desenhar objetos na cena----*/


    glutSwapBuffers(); // Troca os buffers para evitar flickering

}

GLvoid rechapeEcra(GLint largura, GLint altura){
    glViewport(0,0,largura,altura); // Define a viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]); // Define a projecao ortogonal
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GLvoid teclado(unsigned char key, int x, int y){
    GLboolean move = false; // Variável para verificar se a nave se moveu

    switch (key) {
        case 27: // ESC
        //TODO : Pausa do jogo ->
        // glutDisplayFunc(desenhaPausa);
        // glutKeyboardFunc(tecladoPausa);
        // glutIdleFunc(idlePausa);

            exit(0);
            break;
        case 'a': // Movimento para a esquerda
        case 'A':
            move = naveJogador->moverNaveJogador(1); // Move a nave para a esquerda
            break;
        case 'd': // Movimento para a direita
        case 'D':
            move = naveJogador->moverNaveJogador(0); // Move a nave para a direita
            break;
        case 'w': // Movimento para cima
        case 'W':
            move = naveJogador->moverNaveJogador(2); // Move a nave para cima
            break;
        case 's': // Movimento para baixo
        case 'S':
            move = naveJogador->moverNaveJogador(3); // Move a nave para baixo
            break;
    }
    if (move) {
        std::cout << "Nave movida!" << std::endl;
        glutPostRedisplay(); // Redesenha a cena
    } else {
        std::cout << "Movimento inválido!" << std::endl;
    }
    
}

int main(int argc, char** argv){

    glutInit(&argc, argv); // Iniciar GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );// quando a janela é criada, o modo de exibição é definido como RGBA e com duplo buffer
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,600); //Definir o tamanho do ecra

    glutCreateWindow("Alien Invasion"); // Cria o ecra com o titulo

    std::cout << "A iniciar o jogo Alien Invasion..." << std::endl;

    // Inicializa a nave do jogador
    criarNaveJogador();




    /*----CALLBACKS----*/
    glutDisplayFunc(desenhaEcraPrincipal);
    glutReshapeFunc(rechapeEcra);
    glutKeyboardFunc(teclado);
    /*----FIM CALLBACKS----*/




    glutMainLoop(); // Inicia o ciclo de envetos GLUT

    return 0; // retorna 0 para indicaar que o programa finalizou com sucesso

}
// Fim do ficheiro main.cpp