#ifndef TEXT_H
#define TEXT_H
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shader/Shader.h"

using namespace std;

struct Character {
	GLuint     TextureID;  // 字形纹理ID
	glm::ivec2 Size;       // 字形大大小
	glm::ivec2 Bearing;    // 字形基于基线和起点的位置
	GLuint     Advance;    // 起点到下一个字形起点的距离
};

class Text
{
public:
	Text();
	~Text();
	void LoadChar();
	void setBuffers();
	void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	GLuint VAO, VBO;
	FT_Face face;
	FT_Library ft;
	map<GLchar, Character> Characters;
};



#endif