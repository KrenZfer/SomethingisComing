#include "TextsHandler.h"

TextstHandler::TextstHandler(){
	graphic = GraphicHandler();
}

TextstHandler::~TextstHandler(){}

void TextstHandler::InitFont(int fontsizes, const char* fontnames) {
	this->FONTNAMETEXT = fontnames;
	this->FONTSIZE = fontsizes;
	// Init Freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		Err("ERROR::FREETYPE: Could not init FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, FONTNAMETEXT, 0, &face)) {
		Err("ERROR::FREETYPE: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, FONTSIZE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
		GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->program = graphic.BuildShader("font.vert", "font.frag");
}

void TextstHandler::Render(string texts, GLfloat x, GLfloat y, GLfloat scale, vec3 color, unsigned int screenWidth, unsigned int screenHeight) {
	mat4 projection = ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	GLint location = glGetUniformLocation(this->program, "projection");
	graphic.UseShader(this->program);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderText(texts, x, y, scale, color);

	glDisable(GL_BLEND);
}

void TextstHandler::RenderText(string texts, GLfloat x, GLfloat y, GLfloat scale, vec3 color) {
	this->TEXT = texts;
	this->xPosText = x;
	this->yPosText = y;
	this->scaleText = scale;
	this->colorText = color;
	// Activate corresponding render state
	graphic.UseShader(this->program);
	glUniform3f(glGetUniformLocation(this->program, "textColor"), this->colorText.x, this->colorText.y, this->colorText.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	string::const_iterator c;
	for (c = TEXT.begin(); c != TEXT.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat xpos = this->xPosText + ch.Bearing.x * this->scaleText;
		GLfloat ypos = this->yPosText - (ch.Size.y - ch.Bearing.y) * this->scaleText;
		GLfloat w = ch.Size.x * this->scaleText;
		GLfloat h = ch.Size.y * this->scaleText;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1 / 64 pixels)
		this->xPosText += (ch.Advance >> 6) * this->scaleText; // Bitshift by 6 to get value in pixels(2 ^ 6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextstHandler::UpdateText(string texts) {
	this->TEXT = texts;
}

void TextstHandler::Err(string ErrorString) {
	cout << ErrorString << endl;
	SDL_Delay(1000);
	SDL_Quit();
	exit(1);
}