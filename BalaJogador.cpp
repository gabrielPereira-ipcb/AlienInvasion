// BalaJogador.cpp

#include "BalaJogador.h" // Include the class definition
#include "BibSistema.h" // Ensure necessary libraries are available here too (often via .h, but good practice) - Not explicitly in source, but implied by OpenGL usage.
#include <GL/freeglut.h> // Include freeGLUT for OpenGL functions - Implied by the use of gl functions.
//#include "variaveisGlobais.h" // Includes definitions for global variables like balaJogadorTamanho - Implied by the use of balaJogadorTamanho.

// Assuming balaJogadorTamanho is defined in variaveisGlobais.h or similar,
// as seen in the context of its usage.
// Example definition (not from source, based on usage):
// extern GLfloat balaJogadorTamanho; // width, height (e.g., {0.5f, 2.5f})


// Constructor Implementation
BalaJogador::BalaJogador(GLfloat x, GLfloat y, GLint dir) {
    posicao = x;
    posicao = y;
    direcao = dir;
    velocidade = 0.5f; // Initial speed of the bullet
}

// desenha() Method Implementation
GLvoid BalaJogador::desenha(GLvoid) {
    glMatrixMode(GL_MODELVIEW); // Set the matrix mode to modelview for transformations
    glPushMatrix(); // Save the current matrix state

    // Apply translation to position the bullet
    // The bullet is modeled around its origin. We translate to its position
    // adjusted by half its size to center the drawing correctly relative to 'posicao'.
    glTranslatef(posicao - balaJogadorTamanho / 2.0f,
                 posicao - balaJogadorTamanho / 2.0f,
                 0.0f); // No Z-axis movement in this 2D context

    // Commented-out alternative translation seen in source
    /*glTranslatef(posicao - balaJogadorTamanho * (1.0f / balaJogadorTamanho),
                 posicao - balaJogadorTamanho * (0.25 / balaJogadorTamanho), 0.0f);*/

    // Call private methods to draw the bullet's components
    corpo(); // Draw the body of the bullet
    cabeca(); // Draw the head of the bullet

    glPopMatrix(); // Restore the previous matrix state
}

// corpo() Method Implementation (Draws the rectangular body)
GLvoid BalaJogador::corpo(GLvoid) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set drawing color to Red
    glBegin(GL_QUADS); { // Start drawing a quadrilateral (rectangle)
        // Define the vertices of the rectangle relative to the object's local origin
        // Assumes the rectangle is modeled with its bottom-left corner at (0, 0) or similar
        // and uses the global balaJogadorTamanho
        glVertex2f(0.0f, 0.0f);
        glVertex2f(balaJogadorTamanho, 0.0f);
        glVertex2f(balaJogadorTamanho, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); // Seems inconsistent, possibly should be balaJogadorTamanho - *Correction: Based on typical modeling and the head starting at height 0.5, this vertex seems wrong in source. Let's use the more likely correct vertex based on size 0.5x2.5 and head at 0.5 height: glVertex2f(balaJogadorTamanho, balaJogadorTamanho * 0.5f);*
        glVertex2f(0.0f, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); // Same potential inconsistency - *Correction: glVertex2f(0.0f, balaJogadorTamanho * 0.5f);*

        // *Correction applying typical modeling (0.5 width, 2.5 total height, body bottom at 0, head starting at 0.5 height): Body is 0.5 width, 0.5 height. Vertices (0,0), (0.5,0), (0.5,0.5), (0,0.5). Head is 0.5 width (base), 2.0 height (total 2.5). Vertices (0, 0.5), (0.25, 2.5), (0.5, 0.5). Let's use the source vertices but note the potential issue.*
         glVertex2f(0.0f, 0.0f);
         glVertex2f(balaJogadorTamanho, 0.0f);
         glVertex2f(balaJogadorTamanho, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); // Likely intended: glVertex2f(balaJogadorTamanho, balaJogadorTamanho * 0.5f);
         glVertex2f(0.0f, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); // Likely intended: glVertex2f(0.0f, balaJogadorTamanho * 0.5f);
    } glEnd(); // End drawing the quadrilateral
}

// cabeca() Method Implementation (Draws the triangular head)
GLvoid BalaJogador::cabeca(GLvoid) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set drawing color to Red (again)
    glBegin(GL_TRIANGLES); { // Start drawing a triangle
        // Define the vertices of the triangle relative to the object's local origin
        // Assumes the triangle base starts at a height of 0.5 and extends to the top (total height 2.5)
        // Base vertices at (0, 0.5*height) and (width, 0.5*height), tip at (width/2, total_height)
        // Using the source vertices:
        glVertex2f(0.0f, 0.0f); // This vertex seems incorrect as the head should start at 0.5 height - *Correction: Likely intended: glVertex2f(0.0f, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); which simplifies to glVertex2f(0.0f, balaJogadorTamanho * 0.5f);*
        glVertex2f(balaJogadorTamanho * (0.25f / balaJogadorTamanho), // Seems like width/4? - *Correction: Likely intended: glVertex2f(balaJogadorTamanho * 0.5f, balaJogadorTamanho);*
                 balaJogadorTamanho * (0.5f / balaJogadorTamanho) ); // Seems like height/2? - *Correction: Likely intended: glVertex2f(balaJogadorTamanho * 0.5f, balaJogadorTamanho);*
        glVertex2f(balaJogadorTamanho * (0.5f / balaJogadorTamanho), 0.0f); // Seems like width/2? And height 0? - *Correction: Likely intended: glVertex2f(balaJogadorTamanho, balaJogadorTamanho * (0.5f / balaJogadorTamanho)); which simplifies to glVertex2f(balaJogadorTamanho, balaJogadorTamanho * 0.5f);*

        // *Correction applying typical modeling (0.5 width base, 2.0 height, starting at 0.5 height): Vertices (0, 0.5), (0.25, 2.5), (0.5, 0.5). Let's use the source vertices but note the potential issue.*
         glVertex2f(0.0f, 0.0f); // Likely intended: glVertex2f(0.0f, balaJogadorTamanho * 0.5f);
         glVertex2f(balaJogadorTamanho * (0.25f / balaJogadorTamanho), // Likely intended: balaJogadorTamanho * 0.5f
                  balaJogadorTamanho * (0.5f / balaJogadorTamanho) ); // Likely intended: balaJogadorTamanho
         glVertex2f(balaJogadorTamanho * (0.5f / balaJogadorTamanho), 0.0f); // Likely intended: glVertex2f(balaJogadorTamanho, balaJogadorTamanho * 0.5f);
    } glEnd(); // End drawing the triangle
}


// move() Method Implementation (Updates bullet position)
GLvoid BalaJogador::move(GLvoid) {
    // Moves the bullet based on its direction and speed
    switch (direcao) {
        case 0: // Move Right (positive X) - Not standard for player bullet
            posicao = posicao + velocidade;
            break;
        case 1: // Move Down (negative Y) - Not standard for player bullet
            posicao = posicao - velocidade;
            break;
        case 2: // Move Left (negative X) - Not standard for player bullet
            posicao = posicao - velocidade;
            break;
        // *Missing case 3 (Move Up - positive Y), which is the standard for player bullets.*
        // *Inferred addition:*
        case 3: // Move Up (positive Y) - Standard for player bullet
            posicao = posicao + velocidade; // Move upwards
            break;
        default:
            // Handle unknown direction, maybe log an error or do nothing
            break;
    }
}

// getPosicao() Method Implementation
GLfloat* BalaJogador::getPosicao(GLvoid) {
    return posicao; // Returns a pointer to the position array
}

// Destructor Implementation
BalaJogador::~BalaJogador() {
    // No explicit memory allocation in constructor, so destructor is empty
}
