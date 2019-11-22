
/* include custom libraries */
#include "model.h"
#include "timing_utils.h"

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


    // PADDEL 1

    /* Update the object posistions depending on which flag is pressed */
    if (up_key_pressed) {

        // if top vertex not off the top of the screen
        if (paddle1_pos_y <= 0.80f)
          paddle1_pos_y += update_step;
    }

    if (down_key_pressed) {

        // if bottom vertes not off the bottom of the screen
        if (paddle1_pos_y >= -0.80f)
          paddle1_pos_y -= update_step;
    }


    // PADDEL 2

    /* Update the object posistions depending on which flag is pressed */
    if (w_key_pressed) {

        // if top vertex not off the top of the screen
        if (paddle2_pos_y <= 0.80f)
          paddle2_pos_y += update_step;
    }

    if (s_key_pressed) {

        // if bottom vertes not off the bottom of the screen
        if (paddle2_pos_y >= -0.80f)
          paddle2_pos_y -= update_step;
    }


    /* BALL */

    // printf("Ball (%.2f %.2f), UP: %d RIGHT: %d\n", ball_pos_x, ball_pos_y, ball_x_up, ball_y_right);

    if (ball_pos_y >= 0.95f)
      ball_y_up = false;

    if (ball_pos_y <= -0.95f)
      ball_y_up = true;

    if (ball_pos_x >= 0.95f)
      ball_x_right = false;

    if (ball_pos_x <= -0.95f)
      ball_x_right = true;

    // ball hits right paddle
    if (ball_pos_x >= 0.85f && ball_pos_x <= 0.90f) {
      printf("Right Zone\n");
      if (ball_pos_y <= paddle1_pos_y + 0.2f && ball_pos_y >= paddle1_pos_y - 0.2f)
        ball_x_right = false;
    }

    // ball hits left paddle
    if (ball_pos_x <= -0.85f && ball_pos_x >= -0.90f) {
      printf("Left Zone\n");
      if (ball_pos_y <= paddle2_pos_y + 0.2f && ball_pos_y >= paddle2_pos_y - 0.2f)
        ball_x_right = true;
    }

    if (ball_y_up)
      ball_pos_y += update_step * 0.10;
    else
      ball_pos_y -= update_step * 0.10;

    if (ball_x_right)
      ball_pos_x += update_step * 0.12;
    else
      ball_pos_x -= update_step * 0.12;

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

  /* PADDEL 1 */
  GLfloat World[4][4];

  World[0][0] = 1.0f; World[0][1] = 0.0f; World[0][2] = 0.0f; World[0][3] = 0.0f;
  World[1][0] = 0.0f; World[1][1] = 1.0f; World[1][2] = 0.0f; World[1][3] = paddle1_pos_y;
  World[2][0] = 0.0f; World[2][1] = 0.0f; World[2][2] = 1.0f; World[2][3] = 0.0f;
  World[3][0] = 0.0f; World[3][1] = 0.0f; World[3][2] = 0.0f; World[3][3] = 1.0f;

  /* PADDEL 1 */
  GLfloat World2[4][4];

  World2[0][0] = 1.0f; World2[0][1] = 0.0f; World2[0][2] = 0.0f; World2[0][3] = 0.0f;
  World2[1][0] = 0.0f; World2[1][1] = 1.0f; World2[1][2] = 0.0f; World2[1][3] = paddle2_pos_y;
  World2[2][0] = 0.0f; World2[2][1] = 0.0f; World2[2][2] = 1.0f; World2[2][3] = 0.0f;
  World2[3][0] = 0.0f; World2[3][1] = 0.0f; World2[3][2] = 0.0f; World2[3][3] = 1.0f;


  /* BALL */

  GLfloat World3[4][4];

  World3[0][0] = 1.0f; World3[0][1] = 0.0f; World3[0][2] = 0.0f; World3[0][3] = ball_pos_x;
  World3[1][0] = 0.0f; World3[1][1] = 1.0f; World3[1][2] = 0.0f; World3[1][3] = ball_pos_y;
  World3[2][0] = 0.0f; World3[2][1] = 0.0f; World3[2][2] = 1.0f; World3[2][3] = 0.0f;
  World3[3][0] = 0.0f; World3[3][1] = 0.0f; World3[3][2] = 0.0f; World3[3][3] = 1.0f;

  /*
  glUnifrom is a data type used to pass values to a shader program
  glUniformMatrix4fv passes a 4x4 matrix of floating point values.

  1. - The first parameter is a handle for where the 4x4 matrix will be stored in memory
  2, - The second parameter is the number of 4x4 matricies we're going to pass
  3. - The third parameter is whether the 4x4 matrix will be transposed
  4. - The forth parameter is a pointer to the start of the array containing the matrix
  */
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &World[0][0]);
  glBindVertexArray(paddle1.VAO);

  /*
  glDrawElements draws the provided verticies in the order provided by the EBO

  1. - type of primative to draw
  2. - number of elements to draw
  3. - datatype of element array in the EBO (we used GLuint)
  4. - offest of the element array
  */
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


  // Draw second object
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &World2[0][0]);
  glBindVertexArray(paddle2.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  /* BALL */
  glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &World3[0][0]);
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
