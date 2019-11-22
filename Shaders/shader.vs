#version 450 core

layout (location = 0) in vec3 pos_vs;
layout (location = 1) in vec3 color_vs;

out vec3 color_fs;

uniform mat4 Model;

void main()
{
  color_fs = color_vs;
  gl_Position = Model * vec4(pos_vs.x, pos_vs.y, pos_vs.z, 1.0);
}
