#include "Shader.h"

Shader::Shader() { }

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath) {
    // read the glsl file
    FILE *vf, *ff;
    if (fopen_s(&vf, vertexPath, "r")) {
        printf("Fail to open vertex src");
        exit(-1);
    }
    if (fopen_s(&ff, fragmentPath, "r")) {
        printf("Fail to open fragment src");
        exit(-1);
    }

    // read all content in file
    char vs[2049] = { 0 }, fs[2049] = { 0 }, vstmp[2049] = { 0 }, fstmp[2049] = { 0 };
    while ((fgets(vstmp, 2048, vf)) != NULL) {
        strcat_s(vs, 2048, vstmp);
    }
    while ((fgets(fstmp, 2048, ff)) != NULL) {
        strcat_s(fs, 2048, fstmp);
    }
    fclose(vf);
    fclose(ff);

    glsl vertexShaderSource = vs;
    glsl fragmentShaderSource = fs;

    // Vertex shader & Compile
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader, GL_COMPILE_STATUS);

    // Fragment shader & Complie
    unsigned int framentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(framentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(framentShader);
    checkShaderCompile(framentShader, GL_COMPILE_STATUS);
    
    // Shader program & link
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, framentShader);
    glLinkProgram(ID);
    checkShaderCompile(ID, GL_LINK_STATUS);

    // Delete shader
    glDeleteShader(vertexShader);
    glDeleteShader(framentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}