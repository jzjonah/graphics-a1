#include "flea.h"
#include "main.h"
#include "worldDefs.h"




GLuint Flea::VAO = 0;
void Flea::generateVAOs()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Define the VBO

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Define the attributes

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0); // two floats for a position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); // three floats for a colour
    glEnableVertexAttribArray(1);

    // Stop setting up this VAO.

    glBindVertexArray(0);

    // Find line width 'lw' in world coordinate system

    
    float lw = 0.005; // relies on top-bottom = 2 in WCS

    // ---------------- Set up the mushroom geometry ----------------
    //
    // This dummy code just builds a small square centred at (0,0).

    int numVerts = 10;
    int numFloats = 5 * numVerts;  // five attributes for each vertex

    float* buffer = new float[numFloats];

    int i = 0;

    // Vertex 1

    buffer[i++] = -0.015 + lw;
    buffer[i++] = -0.015 + lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    buffer[i++] = -0.015 - lw;
    buffer[i++] = -0.015 - lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    // Vertex 2

    buffer[i++] = +0.015 - lw;
    buffer[i++] = -0.015 + lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    buffer[i++] = +0.015 + lw;
    buffer[i++] = -0.015 - lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    // Vertex 3

    buffer[i++] = +0.015 - lw;
    buffer[i++] = +0.015 - lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    buffer[i++] = +0.015 + lw;
    buffer[i++] = +0.015 + lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    // Vertex 4

    buffer[i++] = -0.015 + lw;
    buffer[i++] = +0.015 - lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    buffer[i++] = -0.015 - lw;
    buffer[i++] = +0.015 + lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    // and back to Vertex 1

    buffer[i++] = -0.015 + lw;
    buffer[i++] = -0.015 + lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;

    buffer[i++] = -0.015 - lw;
    buffer[i++] = -0.015 - lw;

    buffer[i++] = 1;
    buffer[i++] = 1;
    buffer[i++] = 1;


    glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
};



void Flea::draw(mat4& worldToViewTransform)
{

    mat4 T = translate(pos.x, pos.y, 0);
    mat4 MVP = worldToViewTransform * T;

    gpuProg->setMat4("MVP", MVP);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);

    glBindVertexArray(0);

}