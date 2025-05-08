#version 330 core
out vec4 FragColor;

in vec3 position;

uniform float u_wavelength;
uniform float u_hole_radius;
uniform float u_distance;
uniform bool  u_show_grid;

void main()
{
    float r = u_hole_radius * 1e-3;;
    float lambda = u_wavelength * 1e-9;;
    float b = u_distance * 1e-3;
    float rho = distance(position, vec3(0.0f, 0.0f, 0.0f)) * (1e-2 * 10 / 2); //< screen width = 10 cm

    float m = r*r / (lambda * b) * (1 - rho*rho / (2*b*b));

    float cosinus = cos(3.1417 * m / 2);

    float I = cosinus * cosinus;

    if (u_show_grid && (int((position.x + 1.0f) * 500) % 100 == 0 || int((position.y + 1.0f) * 500) % 100 == 0))
        FragColor = vec4(0.7f, 0.0f, 0.0f, 1.0f);
    else
        FragColor = vec4(I, I, I, 1.0f);
}

