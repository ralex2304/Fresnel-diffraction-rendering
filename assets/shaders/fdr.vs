#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 position;

uniform float u_wavelength;
uniform float u_hole_radius;
uniform float u_screen_distance;
uniform bool u_show_grid;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    position = aPos;
}

