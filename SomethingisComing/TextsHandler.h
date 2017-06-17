#ifndef _H_TEXTS_HANDLER_H
#define _H_TEXTS_HANDLER_H

#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>
#include <GLM/glm.hpp>


#include "GraphicHandler.h"

using namespace std;

class TextstHandler {

public:
	TextstHandler();
	~TextstHandler();

	void InitFont(int fontsizes, const char* fontnames);
	void Render(string texts, GLfloat x, GLfloat y, GLfloat scale, vec3 color, unsigned int screenWidth, unsigned int screenHeight);
	void UpdateText(string texts);
	GLfloat getWidthFont() { return width; }
	GLfloat getHeightFont() { return height; }
private:

	struct Character {
		GLuint TextureID; // ID handle of the glyph texture
		ivec2 Size; // Size of glyph
		ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance; // Offset to advance to next glyph
	};

	const char* FONTNAMETEXT;
	int FONTSIZE;
	string TEXT;
	GLfloat xPosText, yPosText, scaleText;
	GLfloat width, height;
	vec3 colorText;
	GLuint VAO, VBO, program;
	GraphicHandler graphic;
	map<GLchar, Character> Characters;

	
	void Err(string ErrorString);
	void RenderText(string texts, GLfloat x, GLfloat y, GLfloat scale, vec3 color);

};

#endif // !_H_TEXTS_HANDLER_H
