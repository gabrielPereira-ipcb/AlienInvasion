// bibSistema.h
#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>

/*A biblioteca freeGLUT (Windows freeglut)será sempre a última a ser adicionada neste ficheiro, daí o espaço deixado
em branco.

*/

// Detecção de sistema operacional para incluir a biblioteca correta
#if defined(_WIN32) || defined (_WIN64)
    #include <GL/freeglut.h>  // Windows usa freeGLUT
#elif defined(__APPLE__) || defined(__MACH__) || defined(TARGET_OS_MAC)
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>  // Em Macs, GLUT é separado
#elif defined(__linux__) 
    #include <GL/glut.h>  // No Linux, basta incluir GLUT
#endif

// --Variaveis GLobais

extern GLfloat coordenadasMundo [4];

//exemplos, podem mudar mais tarde
// extern GLfloat naveJogadorTamanho [2];
// extern GLfloat naveInimigaTamanho [2];
// extern GLfloat balaJogadorTamanho [2];
