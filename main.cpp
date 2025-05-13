//main.cpp
#include "bibSistema.h"


/*******************Variaveis globais*********************************/
GLfloat coordenadasMundo[4] = {-20.0f, 20.0f, -20.0f, 20.0f};

/*******************Variaveis globais FIM ***************************/

// Função para lidar com a entrada do teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case 27:
        std::cout << "A fechar o programa...\n";
        exit(0);
        break;
    }
}

GLvoid idleJogo(GLvoid) {
    // Atualizar a lógica do jogo aqui
    // Por exemplo, mover a nave ou verificar colisões
    // ...
    // Redesenhar a cena
    glutPostRedisplay();
}

GLvoid reshape(int w, int h) {
    // Ajustar a viewport e a projeção quando a janela é redimensionada
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();

}

GLvoid timerJogo(GLint value){
    //TODO: Explicar a diferença entre a funcao timerJogo e idleJogo
    // This function can be used for timed events, like enemy movement or spawning
    // Remember to re-register the timer if it's a one-shot timer
    // glutTimerFunc(milliseconds, timerJogo, value);

    // Request a redraw after updating game state
    glutPostRedisplay();
}

// Função de desenho (callback)
GLvoid draw(GLvoid) {
    std::cout << "Renderizando cena...\n";
    
    // Limpar a tela e definir a cor de fundo (Preto) ----> TODO: nao seria melhor com um fundo igual ao do jogo em fliperama? Como fazer isso?
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);


    // Configurar a projeção 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(coordenadasMundo[0], coordenadasMundo[1], coordenadasMundo[2], coordenadasMundo[3]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // Trocar os buffers para exibir o desenho
    glutSwapBuffers();
}

// Função principal
int main(int argc, char * argv[]) {
    std::cout << "Inicializando GLUTt...\n";
    
    // Inicializar a freeGLUT com os parâmetros da linha de comando
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    // Configurar a janela
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Space Invaders");
    std::cout << "Criando janela...\n";



    // Registar as callbacks
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(draw);
    glutIdleFunc(idleJogo);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timerJogo, 0); 
    //Outras callback serao adiocnadas ao longo do desenvolvimento

    // Iniciar o ciclo de eventos
    glutMainLoop();

    return 0;
}


