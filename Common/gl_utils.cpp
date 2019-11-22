
/* Consult the header file "gl_utils.h" for summary of module contents

*/

#include "gl_utils.h"

using namespace std;

/* Reads a file into a string

- Returns True if successful
- Filename needs to be a constant char array
- Function needs to be passed a pointer (reference) to the string which will contain the file data

TODO: We might be able to make this function static and remove it from the header
static functions can't be called in any file except the one they are declared
while it is possible to declare static functions inside  a head file this is frowned upon since the point of a header file is to be imported by other modules
static functions in C are essentially private helper functions
*/
bool ReadFile(const char* fileName, string& outFile)
{

    // declare variables
    bool ret = false;
    string line;
    ifstream f(fileName);

    if (f.is_open()) {

        // read each line from the file and append to the string
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();
        ret = true;
    }
    else {
        fprintf(stderr, "Failed to open file\n");
    }

    return ret;
}


/* Compile a shader program contained in a string and add it to the GL shader program

- ShaderProgram is an interger handle for the complete shader program which will be used by the GL pipeline
- ShaderText is the contents of a shader program file loaded into char array
- ShaderType should be either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
*/
void AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType)
{

  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(0);
  }

  GLint success;
  GLint text_length[1];
  const GLchar* shader_code[1];

  shader_code[0] = ShaderText;
  text_length[0] = strlen(ShaderText);

  // load and compile the shader code
  glShaderSource(ShaderObj, 1, shader_code, text_length);
  glCompileShader(ShaderObj);
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

  // if there was an error compiling the shader code, print the error log
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: %s\n", ShaderType, InfoLog);
    exit(1);
  }

  glAttachShader(ShaderProgram, ShaderObj);

  return;
}


/* Creates a shader program compiled from the provided vertex shader file and fragment shader file

- vsFileName is the name (and path) to the vertex shader file
- fsFileName is the name (and path) to the fragment shader program
*/
GLuint CompileShaders( const char* vsFileName, const char* fsFileName )
{

  GLint Success = 0;
  GLchar ErrorLog[1024] = {0};
  GLuint ShaderProgram = glCreateProgram();
  string vs, fs;

  if (ShaderProgram == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  if (!ReadFile(vsFileName, vs)) {
    fprintf(stderr, "Failed to read vertex shader file\n");
    exit(1);
  }

  if (!ReadFile(fsFileName, fs)) {
    fprintf(stderr, "Failed to read fragment shader file\n");
    exit(1);
  }

  // Compile the shader code and add it to the GL shader program
  AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
  AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

  // Link the shader program
  glLinkProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

  // Print an error message is linking the shader program failed
  if (Success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error Linking Shader Program: %s\n", ErrorLog);
    exit(1);
  }

  glUseProgram(ShaderProgram);

  return ShaderProgram;
}


/* Creates a glut window given the dimensions and starting location
 - windowHeight is the height of the glut display window in pixels
 - windowWidth is the width of the glut display window in pixels
 - posLeft is the number of pixels to the left of the screen the glut window is created
 - posTop is the number of pixels from the top of the screen the glut window is created
 - windowName is the name of the glut window
*/
void CreateGlutWindow( GLuint windowHeight, GLuint windowWidth, GLuint posLeft, GLuint posTop, const char* windowName )
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(windowHeight, windowWidth);
  glutInitWindowPosition(posLeft, posTop);
  glutCreateWindow(windowName);
}

/* Initialised GLEW and perform an error check to ensure it started correctly */
void InitialiseGlew( void ) {
  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
    exit(1);
  }
}
