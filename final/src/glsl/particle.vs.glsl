#version 330 core
layout (location = 0) in vec3 aPos; // <vec3 position>


out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 offset;
uniform vec4 color;

void main()
{

    ParticleColor = color;
    gl_Position = projection * view * model * vec4(aPos + offset, 1.0);
}