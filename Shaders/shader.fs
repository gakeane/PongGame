#version 450 core

in vec3 color_fs;

out vec4 FragColor;

uniform vec3 DynamicColour;
uniform int DynamicColourSet;

void main()
{

    if (DynamicColourSet == 1) {
        FragColor =  vec4(DynamicColour, 0.0);
    }

    else {
        FragColor =  vec4(color_fs, 0.0);
    }
}
