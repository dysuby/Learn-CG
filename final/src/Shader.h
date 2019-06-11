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
    Shader(const GLchar *vertexPath, const GLchar *fragment);

    void use();
    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;

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

