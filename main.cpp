
/* include custom libraries */
#include "model.h"

/* Declare vertex buffer objects as globals since they are used in many functions */
Model paddle1 = Model();
Model paddle2 = Model();
Model ball = Model();

/* Handles to values passed to the shader program */
GLuint worldLocation;

/* values used to track keyboard input */
GLfloat paddle1_pos_y = 0.0f;
GLfloat paddle2_pos_y = 0.0f;
GLfloat ball_pos_x = 0.0f;
GLfloat ball_pos_y = 0.0f;

bool up_key_pressed = false;
bool down_key_pressed = false;
bool w_key_pressed = false;
bool s_key_pressed = false;

bool ball_y_up = true;
bool ball_x_right = true;

unsigned long current_time = 0;
unsigned long previous_time = 0;

/* File names and paths for the shader files */
const char* vsFileName = "Shaders/shader.vs";
const char* fsFileName = "Shaders/shader.fs";

/* This function handles key presses for most of the standard (ASCII) keys on the keyboard - use with glutKeyboardFunc callback */
void handleNormalKeyDownInput(unsigned char key, int mouse_x, int mouse_y)
{

    /* Quit if the escape key is pressed */
    if (key == 27) {
        exit(0);
    }

    /* move object up/down */
    if (key == 'w')
        w_key_pressed = true;

    if (key == 's')
        s_key_pressed = true;
}

/* This function handles key releases for most of the standard (ASCII) keys on the keyboard - use with glutKeyboardFunc callback */
void handleNormalKeyUpInput(unsigned char key, int mouse_x, int mouse_y)
{

    /* move object up/down */
    if (key == 'w')
        w_key_pressed = false;

    if (key == 's')
        s_key_pressed = false;
}

void handleSpecialKeyDownInput(int key, int mouse_x, int mouse_y)
{

    /* move object up/down */
    if (key == GLUT_KEY_UP)
        up_key_pressed = true;

    if (key == GLUT_KEY_DOWN)
        down_key_pressed = true;

}

void handleSpecialKeyUpInput(int key, int mouse_x, int mouse_y)
{

    /* move object up/down */
    if (key == GLUT_KEY_UP)
        up_key_pressed = false;

    if (key == GLUT_KEY_DOWN)
        down_key_pressed = false;

}

/* this function is used to update the position of the onscreen object */
void updateObjectPosition( void ) {

    /*
    calcaulate amount of time since last update
    The amount we update the object position by will be dependent on how much time passed
    */
    unsigned long elapsed_time = 0;
    current_time = timeSinceEpoch();

    if (previous_time != 0) {
        elapsed_time = current_time - previous_time;
    }

    previous_time = current_time;
    float update_step = elapsed_time * 0.000005f;

    paddle1.updatePaddle(up_key_pressed, down_key_pressed, update_step);
    paddle2.updatePaddle(w_key_pressed, s_key_pressed, update_step);

    ball.updateBall(paddle1.pos_y, paddle2.pos_y, update_step);

}

/* Function which is repeatidly called during the glut display Loop

  - Clears the current buffer
  - Creates an array object which will contain verticies
  - loads the vertex buffer object into the array
  - Creates a pointer object to move through the array
  - Calls the draw method to send data to the GL pipeline
  - Swaps in the newly drawn buffer
*/
static void RenderSceneCB( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  updateObjectPosition();


  // Draw first paddle
  paddle1.updateModelMat();
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &paddle1.modelMat[0][0]);
  glBindVertexArray(paddle1.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


  // Draw second object
  paddle2.updateModelMat();
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &paddle2.modelMat[0][0]);
  glBindVertexArray(paddle2.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


  // Draw Ball
  ball.updateModelMat();
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &ball.modelMat[0][0]);
  glBindVertexArray(ball.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Unbind all VAOs so they can not be modified
  glBindVertexArray(0);

  glutSwapBuffers();
}


/* select the function which should determine what is displayed by glut */
static void InitializeGlutCallbacks( void )
{
  glutDisplayFunc(RenderSceneCB);
  glutIdleFunc(RenderSceneCB);

  glutKeyboardFunc(handleNormalKeyDownInput);
  glutKeyboardUpFunc(handleNormalKeyUpInput);
  glutSpecialFunc(handleSpecialKeyDownInput);
  glutSpecialUpFunc(handleSpecialKeyUpInput);
}


/* Create a Buffer object containing all the verticies to be drawn */
static void CreateVertexBuffer()
{

  /* PADDEL 1 */
  vec3 Vertices[4];
  Vertices[0] = vec3( 0.85f,  0.2f,  0.0f );       // top left
  Vertices[1] = vec3( 0.90f, -0.2f,  0.0f );       // bottom right
  Vertices[2] = vec3( 0.85f, -0.2f,  0.0f );       // bottom left
  Vertices[3] = vec3( 0.90f,  0.2f,  0.0f );       // top right

  vec3 Colours[4];
  Colours[0] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours[1] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours[2] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours[3] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE

  GLuint elements[6] = {0, 1, 2, 0, 3, 1};         // order the verticies should be drawn in

  paddle1.initialiseBuffers(Vertices, sizeof(Vertices), elements, sizeof(elements));
  paddle1.initialiseColorBuffer(Colours, sizeof(Colours));

  /* PADDEL 2 */
  vec3 Vertices2[4];
  Vertices2[0] = vec3( -0.90f,  0.2f,  0.0f );       // top left
  Vertices2[1] = vec3( -0.85f, -0.2f,  0.0f );       // bottom right
  Vertices2[2] = vec3( -0.90f, -0.2f,  0.0f );       // bottom left
  Vertices2[3] = vec3( -0.85f,  0.2f,  0.0f );       // top right

  vec3 Colours2[4];
  Colours2[0] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours2[1] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours2[2] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours2[3] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE

  GLuint elements2[6] = {0, 1, 2, 0, 3, 1};         // order the verticies should be drawn in

  paddle2.initialiseBuffers(Vertices2, sizeof(Vertices2), elements2, sizeof(elements2));
  paddle2.initialiseColorBuffer(Colours2, sizeof(Colours2));

  /* BALL */
  vec3 Vertices3[4];
  Vertices3[0] = vec3( -0.05f,  0.05f,  0.00f );       // top left
  Vertices3[1] = vec3(  0.05f, -0.05f,  0.00f );       // bottom right
  Vertices3[2] = vec3( -0.05f, -0.05f,  0.00f );       // bottom left
  Vertices3[3] = vec3(  0.05f,  0.05f,  0.00f );       // top right

  vec3 Colours3[4];
  Colours3[0] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours3[1] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours3[2] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE
  Colours3[3] = vec3( 1.00f,  1.00f,  1.00f );       // WHITE

  GLuint elements3[6] = {0, 1, 2, 0, 3, 1};         // order the verticies should be drawn in

  ball.initialiseBuffers(Vertices3, sizeof(Vertices3), elements3, sizeof(elements3));
  ball.initialiseColorBuffer(Colours3, sizeof(Colours3));
}


int main(int argc, char** argv)
{

  printf("Starting OpenGL with freeglut \n");

  glutInit(&argc, argv);

  CreateGlutWindow(1024, 768, 100, 10, "Tutorial 03");
  // glutFullScreen(); - This can be hard to get out of if escape key is not working

  InitializeGlutCallbacks();

  // Must be done after glut is initalised
  InitialiseGlew();

  glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

  CreateVertexBuffer();

  GLuint shaderProgram = CompileShaders(vsFileName, fsFileName);

  worldLocation = glGetUniformLocation(shaderProgram, "Model");
  assert(worldLocation != 0xFFFFFFFF);

  glutMainLoop();


  return 0;
}
