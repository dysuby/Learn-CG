#version 330 core
out vec4 FragColor;

in vec4 ParticleColor;

void main()
{    
    FragColor = ParticleColor;
}