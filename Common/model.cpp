
#include "model.h"

Model::Model() {

  pos_y = 0.00f;
  pos_y = 0.00f;

  momentum = 0.00f;

  modelMat[0][0] = 1.0f; modelMat[0][1] = 0.0f; modelMat[0][2] = 0.0f; modelMat[0][3] = 0.0f;
  modelMat[1][0] = 0.0f; modelMat[1][1] = 1.0f; modelMat[1][2] = 0.0f; modelMat[1][3] = 0.0f;
  modelMat[2][0] = 0.0f; modelMat[2][1] = 0.0f; modelMat[2][2] = 1.0f; modelMat[2][3] = 0.0f;
  modelMat[3][0] = 0.0f; modelMat[3][1] = 0.0f; modelMat[3][2] = 0.0f; modelMat[3][3] = 1.0f;

}


/* Initialises the vertex position data into the VAO object at position 0, also initalises the element buffer object */
void Model::initialiseBuffers(vec3* vertices, GLuint num_vertices, GLuint* elements, GLuint num_elements) {

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // vertex buffer object
  glGenBuffers(1, &VBO_position);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
  glBufferData(GL_ARRAY_BUFFER, num_vertices, vertices, GL_STATIC_DRAW);


  /*
  glVertexAttribPointer is used to create a pointer for the shader program to a Vertex buffer object
    1. - The index of the VBO which will be given to the shader program (0 for the first VBO, 1 for the second, 2 for the third, etc)
    2. - The number of components in each vertex (usually 3 for a 3D point, but might be 4 for a colour)
    3. - The data type of the each component in the vertex
    4. - If we want the verticies to be normalised before passing to the graphics pipeline
    5. - The stride of the vertex data (e.g. every second vertex)
    6. - The offset of the vertex data (e.g. skip the first 5 vertices)

  Used to enable a VBO in the VAO
    1. - The index of the VBO which will be given to the shader program (0 for the first VBO, 1 for the second, 2 for the third, etc)
  */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // we can use another vertex buffer object to store the colour for each vertex

  // we can use another vertex buffer object to store the normals for each vertex

  // Element buffer object is used to specify the order that elements should be drawn in
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_elements, elements, GL_STATIC_DRAW);

  glBindVertexArray(0);

}


/* Initialises the colour vertex buffer object at location 1 in the shader program */
void Model::initialiseColorBuffer(vec3* colors, GLuint num_vertices) {

    glBindVertexArray(VAO);

    // vertex buffer object
    glGenBuffers(1, &VBO_colour);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_colour);
    glBufferData(GL_ARRAY_BUFFER, num_vertices, colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


/* Initialises the normals vertex buffer object at location 2 in the shader program */
void Model::initialiseNormalsBuffer(vec3* normals, GLuint num_vertices) {

    glBindVertexArray(VAO);

    // vertex buffer object
    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, num_vertices, normals, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}




void Model::updatePaddle(bool up_key_pressed, bool down_key_pressed, float update_step) {


    //printf("Momentum: %.4f\n", momentum);

    /* gain momentum when key is pressed */
    if (up_key_pressed || down_key_pressed) {
        if (momentum < 3.00f) {
            momentum += 0.002f;
        }
    }

    /* loose momentum when key not pressed */
    else {
        if (momentum > 0.00f) {
            momentum -= 0.01f;
        }
    }

    /* Ensure momentum is never less than 0 */
    if (momentum < 0.00f) {
        momentum = 0.00f;
    }


    /* Update the object posistions depending on which flag is pressed */
    if (up_key_pressed) {

        // if top vertex not off the top of the screen
        if (pos_y <= 0.80f)
          pos_y += update_step * momentum;
    }

    if (down_key_pressed) {

        // if bottom vertes not off the bottom of the screen
        if (pos_y >= -0.80f)
          pos_y -= update_step * momentum;
    }
}


void Model::updateBall(float paddle1_y_pos, float paddle2_y_pos, float update_step) {

}


void Model::updateModelMat() {
    modelMat[0][3] = pos_x;
    modelMat[1][3] = pos_y;
}
