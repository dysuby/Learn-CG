#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>
#include <cstdio>

typedef const char const* glsl;

class Shader {
public:
    unsigned int ID;
    Shader(const GLchar *vertexPath, const GLchar *fragment);

    void use();

private:
    void checkShaderCompile(unsigned int shader, unsigned int type) {
        int success;
        char infolog[512];
        glGetShaderiv(shader, type, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infolog);
            exit(-1);
        }
    }

};

