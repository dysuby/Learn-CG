#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <cstdio>

typedef const char const* glsl;

class Shader {
public:
    unsigned int ID;
    Shader();
    Shader(const GLchar *vertexPath, const GLchar *fragment);

    void use();
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setFloat(const std::string & name, float value) const;
    void setInt(const std::string & name, int value) const;

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


#endif

