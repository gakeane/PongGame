
/* Class for storing a mesh

Conatins the VAO, VBO and EBO for the mesh
Contains a model matrix for the mesh to position it in the world

*/

#include "gl_utils.h"
#include "math_3d.h"


class Model {
private:
  double momentum;

public:

  GLuint VAO;             // Vertex array object used to hold multiple vertex buffer objects (VBOs) in a single array
  GLuint VBO_position;    // Vertex buffer object used to store the position of all vertices
  GLuint VBO_colour;      // Vertex buffer object used to store the colour of all vertices
  GLuint VBO_normals;     // Vertex buffer object used to store the normals of all vertices
  GLuint EBO;             // Element buffer object used to indicate the order the indicies of the vertex buffer objects (VBOs)
                          // NOTE: We do not require the

  GLfloat modelMat[4][4];

  GLfloat pos_x;
  GLfloat pos_y;


  /* Default constructor */
  Model();

  void initialiseBuffers(vec3* vertices, GLuint num_verticies, GLuint* elements, GLuint num_elements);
  void initialiseColorBuffer(vec3* colors, GLuint num_vertices);
  void initialiseNormalsBuffer(vec3* normals, GLuint num_vertices);

  void updateModelMat();

  void updatePaddle(bool up_key_pressed, bool down_key_pressed, float update_step);
  void updateBall(float paddle1_y_pos, float paddle2_y_pos, float update_step);
};
