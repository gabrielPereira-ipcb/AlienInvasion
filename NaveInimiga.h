#pragma once
#include "BibSistema.h" // Includes standard libs and OpenGL/freeGLUT

// Assume naveInimigoTamanho is declared as a global in bibliotecasSistema.h
extern GLfloat naveInimigaTamanho; // Declared extern as it's defined elsewhere, e.g., in the .cpp or a global file

class NaveInimiga {
private:
    GLfloat posicao; // Stores the ship's position (x, y)
    GLfloat velocidade; // Stores the ship's velocity

    // Private methods to draw each part of the ship, modeled at the origin
    GLvoid corpo(GLvoid); // Draws the ship's body
    GLvoid cockpit(GLvoid); // Draws the ship's cockpit
    GLvoid asaDireita(GLvoid); // Draws the right wing
    GLvoid asaEsquerda(GLvoid); // Draws the left wing
    GLvoid turbo(GLvoid); // Draws the turbo

public:
    NaveInimiga(GLfloat); // Constructor with velocity
    NaveInimiga(GLfloat, GLfloat, GLfloat); // Constructor with initial position and velocity
    GLvoid desenha(GLvoid); // Method to draw the entire ship
    GLvoid move(GLint); // Method to handle ship movement
    GLfloat* getPosicao(GLvoid); // Method to get the ship's position
    ~NaveInimiga(); // Destructor
};
