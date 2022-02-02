// mushroom.cpp


#include "mushroom.h"
#include "main.h"
#include "worldDefs.h"


extern GLFWwindow* window;
#define LINE_HALFWIDTH_IN_PIXELS 2.0


GLuint Mushroom::VAO = 0;
vec2 Mushroom::mushroomgeometry[12] = { // triangle fan of interior
  vec2(-1.5,-1.5),
  vec2(-1.5,-4.5),
  vec2(1.5,-4.5),
  vec2(1.5,-1.5),
  vec2(1.5,-0.5),
  vec2(1.5,1.5),
  vec2(2.5,1.5),
  vec2(.5,4.5),
  vec2(-0.5,4.5),
  vec2(-2.5,1.5),
  vec2(-3.5,1.5),
  vec2(-3.5,-0.5)
};

vec2 Mushroom::mushroomOutline[10] = {
  vec2(-2,-2),
  vec2(-2,-5),
  vec2(2,-5),
  vec2(2,-2),
  vec2(4,-1),
  vec2(4,2),
  
  vec2(1,5),
  vec2(-1,5),
  
  vec2(-4,2),
  vec2(-4,-1)

};



void Mushroom::generateVAOs()

{
    // [YOUR CODE HERE]
    //
    // REPLACE THE CODE in this function to generate VAOs that store
    // mushroom geometry.  You will need MULTIPLE VAOs.  You should look
    // at the Player and the Centipede to see how those multiple VAOs
    // are set up.  You can do something similar here, or take your own
    // approach.
    //
    // For full marks, you should use the parameters in worldDefs.h to
    // determine the SIZE of your geometry.
    //
    // Your geometry should be centred at (0,0) so that you can later
    // translate it to its correct position
    //
    // In Step 5 (after you get the mushroom rendered correctly), also
    // take into account the mushroom's 'damage' to draw a mushroom with
    // the appropriate amount of damage.

    // Start setting up a VAO

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
    db = new DrawBuffers(VAO);
    seq<vec2> positions;
    seq<vec3> colours;



    //int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    //float lw = LINE_HALFWIDTH_IN_PIXELS / (float)height * 2; // relies on top-bottom = 2 in WCS

    // ---------------- Set up the mushroom geometry ----------------
    //
    // This dummy code just builds a small square centred at (0,0).
    int offset = positions.size();
    for (int i = 0; i < 10; i++)
        positions.add((0.6 * ROW_SPACING / 9.0) * mushroomOutline[i] - vec2(0, 0));

    for (int i = 0; i<positions.size(); i++)
        colours.add((MUSH_OUTLINE_COLOUR));
    
    db->mode.add(GL_TRIANGLE_FAN);
    db->first.add(offset);
    db->count.add(positions.size() - offset);

    offset = positions.size();

    for (int i = 0; i < 12; i++)
        positions.add((0.6 * ROW_SPACING / 9.0) * mushroomgeometry[i] - vec2(0, 0));

    
    for (int i = 0; i < positions.size(); i++)
        colours.add((MUSH_BODY_COLOUR));

    db->mode.add(GL_TRIANGLE_FAN);
    db->first.add(offset);
    db->count.add(positions.size() - offset);

            

    
    int numFloats = positions.size()* 5;  // five attributes for each vertex

    float* buffer = new float[numFloats];
    
    float* p = buffer;

        for (int i = 0; i < positions.size(); i++) {
            *p++ = positions[i].x;
            *p++ = positions[i].y;
            *p++ = colours[i].x;
            *p++ = colours[i].y;
            *p++ = colours[i].z;
        }


    glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void Mushroom::draw(mat4& worldToViewTransform)

{
    // [YOUR CODE HERE]
    //
    // REPLACE THE CODE in this function so that your mushroom is drawn
    // centred at its 'pos'.
    //
    // Later, in Step 5, also take into account the mushroom's 'damage'
    // to draw a mushroom with the appropriate amount of damage.

    // Provide MVP to GPU program

    mat4 T = translate(pos.x, pos.y, 0);
    mat4 MVP = worldToViewTransform * T;

    gpuProg->setMat4("MVP", MVP);

    db->draw();
}

DrawBuffers* Mushroom::db = NULL;

