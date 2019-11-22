
#include <stdio.h>

#ifdef WIN32
#include <cmath>
#else
#include <math.h>
#endif

#define ToRadian(x) (float)(x * M_PI / 180.0f)
#define ToDegree(x) (float)(x * 180.0f / M_PI)

class vec3 {
public:
  float x;
  float y;
  float z;

  /* Default Constructor - initalise values to zero*/
  vec3( void ) {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  /* Constructor - initialise values with three floats */
  vec3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  /* Constructor - initialise all values to the same float */
  vec3(float f) {
    x = y = z = f;
  }

  /* Operator overload - overload addition opperator */
  vec3& operator+(const vec3& r) {
    x += r.x;
    y += r.y;
    z += r.z;

    return *this;
  }

  /* Operator overload - overload subtraction opperator */
  vec3& operator-(const vec3& r) {
    x -= r.x;
    y -= r.y;
    z -= r.z;

    return *this;
  }

  /* Operator overload - overload multiplication opperator */
  vec3& operator*(float f) {
    x *= f;
    y *= f;
    z *= f;

    return *this;
  }

  /* print vector on a new line */
  void print( void );
};
