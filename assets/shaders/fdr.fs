#version 330 core
out vec4 FragColor;

in vec3 position;

void main()
{
    float r = 1.0;
    float lambda = 1.0;
    float b = 0.2;
    float rho = distance(position, vec3(0.0f, 0.0f, 0.0f));

    float m = r*r / (lambda * b) * (1 - rho*rho / (2*b*b));

    float cosinus = cos(3.1417 * m / 2);

    float I = cosinus * cosinus;

    FragColor = vec4(I, I, I, 1.0f);
}

