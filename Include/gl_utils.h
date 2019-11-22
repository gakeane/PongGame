
/*
Module:
 - Includes GL libraries
 - Common functionality relating the GL pipeline and GL libraries
*/

/* System dependent libraries */
#ifndef WIN32
#include <unistd.h>
#endif

#include <windef.h>    // this is need to prevent some compiler errors in glu.h

/* standard C libraries */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* standard C++ libraries which are part of the std namespace */
#include <string>
#include <fstream>

/* 3rd party libraries */
#include "GL/glew.h"          // must be included before gl.h, glu.h and freeglut.h
#include "GL/freeglut.h"

/* Reads a file into a string */
bool ReadFile( const char* fileName, std::string& outFile );

/* Load and compile shader code into a shader program */
void AddShader( GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType );

/* Create a shader program from the provided vertex and fragment shader files */
GLuint CompileShaders( const char* vsFileName, const char* fsFileName );

/* Creates a glut window given the dimensions and starting location */
void CreateGlutWindow( GLuint windowHeight, GLuint windowWidth, GLuint posLeft, GLuint posTop, const char* windowName );

/* Initialised GLEW and perform an error check to ensure it started correctly */
void InitialiseGlew( void );
