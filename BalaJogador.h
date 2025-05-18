// BalaJogador.h

#pragma once // Ensures this header is only included once during compilation

#include "BibSistema.h" // Includes necessary system libraries (e.g., freeGLUT)

// Class definition for the Player's Bullet
class BalaJogador {
private:
    // Attributes to define the bullet's state
    GLfloat posicao; // Current position (x, y) in the game world
    GLfloat velocidade; // Speed of the bullet
    GLint direcao;      // Direction of movement (e.g., 0=right, 1=down, 2=left, 3=up)

    // Private helper methods for drawing the bullet's components
    GLvoid corpo(GLvoid);    // Draws the body of the bullet
    GLvoid cabeca(GLvoid);   // Draws the head of the bullet

public:
    // Constructor: Initializes the bullet's position and direction
    BalaJogador(GLfloat x, GLfloat y, GLint dir);

    // Method to draw the bullet at its current position
    GLvoid desenha(GLvoid);

    // Method to update the bullet's position over time
    GLvoid move(GLvoid);

    // Getter method to retrieve the bullet's current position
    GLfloat* getPosicao(GLvoid); // Returns a pointer to the position array

    // Destructor: Cleans up resources if necessary
    ~BalaJogador();
};
