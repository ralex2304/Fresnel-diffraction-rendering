#version 330 core
out vec4 FragColor;

in vec3 position;

uniform bool  u_show_pattern;
uniform bool  u_show_grid;
uniform float u_slit_width;
uniform float u_wavelength;
uniform float u_distance;

void main()
{
    float d = distance(position, vec3(0.0f, 0.0f, 0.0f));
    FragColor = vec4(sin(d * 100.0f) * asin(position.x / position.y),
                     sin(d * 100.0f) * asin(position.y / position.x),
                     0.0f,
                     1.0f);
}

