#include "NaveInimiga.h" // Includes the class definition

// Definition for the global variable (assumed to be defined once in a .cpp file)
// Placeholder values based on report description (5 width, 2 height)
// These values are used in drawing and positioning logic.
GLfloat naveInimigaTamanho = {5.0f, 2.0f};

// Constructor with velocity (based on structure from)
NaveInimiga::NaveInimiga(GLfloat veloc) {
    posicao = 0.0f; // Initialize x position
    posicao = 0.0f; // Initialize y position
    velocidade = veloc; // Set velocity
}

// Constructor with initial position and velocity (based on structure from)
NaveInimiga::NaveInimiga(GLfloat x, GLfloat y, GLfloat veloc) {
    posicao = x; // Set initial x position
    posicao = y; // Set initial y position
    velocidade = veloc; // Set velocity
}

// Implementation of the private drawing method for the body
GLvoid NaveInimiga::corpo(GLvoid) {
    // Set color for the body (Light Blue)
    glColor3f(0.0f, 0.8f, 1.5f); // Color specified in source, described as light blue
    glBegin(GL_QUADS); { // Start drawing a quadrilateral
        // Vertices defined relative to the local origin (0,0)
        // The source uses naveInimigoTamanho for calculating vertices,
        // which simplifies assuming naveInimigoTamanho and are non-zero.
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, naveInimigaTamanho); // Equivalent to naveInimigoTamanho * (1.0f / naveInimigoTamanho)
        glVertex2f(naveInimigaTamanho, naveInimigaTamanho); // Equivalent to naveInimigoTamanho * (2.0f / naveInimigoTamanho), naveInimigoTamanho * (1.0f / naveInimigoTamanho)
        glVertex2f(naveInimigaTamanho, 0.0f); // Equivalent to naveInimigoTamanho * (2.0f / naveInimigoTamanho), 0.0f
    } glEnd(); // End drawing the quadrilateral
}

// --- Private drawing methods for other parts ---
// NOTE: While these methods are declared and mentioned as parts,
// their exact vertex coordinates were not fully detailed in the provided text sources.
// The implementations below use simple primitives and colors mentioned,
// but the specific vertex values are inferred based on typical ship geometry and the report's figures,
// NOT copied verbatim from the source text.
GLvoid NaveInimiga::cockpit(GLvoid) {
    // Set color for the cockpit (Dark Blue)
    glColor3f(0.0f, 0.0f, 0.5f); // Example Dark Blue
    glBegin(GL_TRIANGLES); { // Assuming cockpit is a triangle based on enemy figures
        // Example vertices, relative to local origin (specific values not in source text)
        glVertex2f(naveInimigaTamanho * 0.25f, naveInimigaTamanho);
        glVertex2f(naveInimigaTamanho * 0.75f, naveInimigaTamanho);
        glVertex2f(naveInimigaTamanho * 0.5f, naveInimigaTamanho * 1.5f);
    } glEnd(); // End drawing
}

GLvoid NaveInimiga::asaDireita(GLvoid) {
    // Set color for the right wing (Pink)
    glColor3f(1.0f, 0.7f, 0.8f); // Example Pink
    glBegin(GL_TRIANGLES); { // Wings are triangles
        // Example vertices, relative to local origin (specific values not in source text)
        glVertex2f(naveInimigaTamanho, naveInimigaTamanho * 0.25f);
        glVertex2f(naveInimigaTamanho + naveInimigaTamanho * 0.5f, 0.0f);
        glVertex2f(naveInimigaTamanho, 0.0f);
    } glEnd(); // End drawing
}

GLvoid NaveInimiga::asaEsquerda(GLvoid){
    // Set color for the left wing (Pink)
    glColor3f(1.0f, 0.7f, 0.8f); // Example Pink
    glBegin(GL_TRIANGLES); { // Wings are triangles
        // Example vertices, relative to local origin (specific values not in source text)
        glVertex2f(0.0f, naveInimigaTamanho * 0.25f);
        glVertex2f(-naveInimigaTamanho * 0.5f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    } glEnd(); // End drawing
}

GLvoid NaveInimiga::turbo(GLvoid){
    // Set color for the turbo (Dark Blue)
    glColor3f(0.0f, 0.0f, 0.5f); // Example Dark Blue
    glBegin(GL_QUADS); { // Assuming turbo is a quad based on enemy figures
        // Example vertices, relative to local origin (specific values not in source text)
        glVertex2f(naveInimigaTamanho * 0.4f, 0.0f);
        glVertex2f(naveInimigaTamanho * 0.6f, 0.0f);
        glVertex2f(naveInimigaTamanho * 0.6f, -naveInimigaTamanho * 0.5f);
        glVertex2f(naveInimigaTamanho * 0.4f, -naveInimigaTamanho * 0.5f);
    } glEnd(); // End drawing
}
// --- End of Private drawing methods ---


// Implementation of the desenha() method
GLvoid NaveInimiga::desenha(GLvoid) {
    // Set matrix mode to Modelview
    glMatrixMode(GL_MODELVIEW);
    // Save the current matrix state before applying transformations for this ship
    glPushMatrix();

    // Apply the main translation to move the ship's local origin to its world position
    // The source provides specific calculation:
    glTranslatef(posicao - naveInimigaTamanho / naveInimigaTamanho, // This simplifies to posicao - 1.0f
                 posicao - naveInimigaTamanho / 4.0f, // This simplifies to posicao - 0.5f, assuming naveInimigoTamanho is 2.0f
                 0.0f); // No Z translation for 2D rendering

    // Draw the main body of the ship. It is modeled at the origin (0,0).
    // After the main translation, drawing at (0,0) will place it at the ship's world position adjusted by the offset above.
    corpo();

    // Draw other parts by applying transformations relative to the ship's current origin (which is now translated)
    // We push/pop the matrix for each part to ensure transformations are independent.

    glPushMatrix(); // Save matrix before drawing cockpit
    // Translate to position the cockpit relative to the ship's body
    // Source uses: glTranslatef(naveInimigoTamanho * (0.5f / naveInimigoTamanho), naveInimigoTamanho * (1.0f / naveInimigoTamanho), 0.0f);
    // This simplifies to glTranslatef(0.5f, 1.0f, 0.0f);
    // Example relative positioning based on modeling. Adjust if needed based on actual part vertices.
    glTranslatef(naveInimigaTamanho * 0.5f, naveInimigaTamanho, 0.0f);
    cockpit(); // Draw the cockpit
    glPopMatrix(); // Restore matrix after drawing cockpit

    glPushMatrix(); // Save matrix before drawing right wing
    // Translate to position the right wing relative to the ship's origin
    // Example relative positioning. Adjust if needed based on actual part vertices.
    glTranslatef(naveInimigaTamanho, naveInimigaTamanho * 0.25f, 0.0f);
    asaDireita(); // Draw the right wing
    glPopMatrix(); // Restore matrix

    glPushMatrix(); // Save matrix before drawing left wing
    // Translate to position the left wing relative to the ship's origin
    // Example relative positioning. Adjust if needed based on actual part vertices.
     glTranslatef(0.0f, naveInimigaTamanho * 0.25f, 0.0f);
    asaEsquerda(); // Draw the left wing
    glPopMatrix(); // Restore matrix

    glPushMatrix(); // Save matrix before drawing turbo
    // Translate to position the turbo relative to the ship's origin
    // Example relative positioning. Adjust if needed based on actual part vertices.
    glTranslatef(naveInimigaTamanho * 0.5f, 0.0f, 0.0f); // Position centered at the bottom of the body
    turbo(); // Draw the turbo
    glPopMatrix(); // Restore matrix


    // Restore the matrix state to what it was before drawing this ship
    glPopMatrix();
}

// Implementation of the move() method
// The sources describe that enemy movement is handled by updating their position
// based on a simple pattern and checking for boundary collisions.
// The exact implementation details for this method are not fully provided in the text sources.
GLvoid NaveInimiga::move(GLint direcao) {
    // Placeholder implementation structure based on source descriptions:
    // Update 'posicao' or 'posicao' based on 'direcao' and 'velocidade'.
    // Example: if (direcao == 0) { // Move Right
    //              posicao += velocidade;
    //          }
    // Check boundaries (using 'coordenadasMundo' global, if defined).
    // Example: if (posicao > coordenadasMundo - naveInimigoTamanho/2.0f) {
    //              posicao = coordenadasMundo - naveInimigoTamanho/2.0f;
    //              // Change direction, e.g., naveInimigoDirecao = 2 (Left)
    //          }
}

// Implementation of the getPosicao() method
GLfloat* NaveInimiga::getPosicao(GLvoid) {
    // Returns a pointer to the position array
    return posicao;
}

// Implementation of the destructor
NaveInimiga :: ~NaveInimiga() {
    // Destructor is empty in the source, suggesting no dynamic memory allocation
    // within the class itself that requires explicit cleanup.
}
