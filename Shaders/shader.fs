#version 450 core

in vec3 color_fs;

out vec4 FragColor;

void main()
{
  FragColor =  vec4(color_fs, 0.0);
}
