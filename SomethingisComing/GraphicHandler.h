#ifndef _GRAPHIC_HANDLER_
#define _GRAPHIC_HANDLER_

#include <SDL/SDL.h>
#include <SOIL/SOIL.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include "Camera.h"

using namespace std;
using namespace glm;

class GraphicHandler {

public:
	GraphicHandler();
	~GraphicHandler();
	GLuint VAO, VBO, buffervertexs, bufferuvs, buffernormals, texture;
	GLuint shader;
	Camera camera;
	vec3 lightPos;
	vec3 charPosition;
	unsigned int screenWidth, screenHeight;
	vector<vec3> verticesObject, normalsObject;
	vector<vec2> uvsObject;
	mat4 TMatrix, RMatrix, SMatrix;
	mat4 model, view, projection;
	GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void UseShader(GLuint program);
	bool loadObject(const char* path,
		vector <vec3> & out_vertices,
		vector <vec2> & out_uvs,
		vector <vec3> & out_normals);
	void BuildObject(char* pathShaderVert, char* pathShaderFrag, char* pathOBJ, char* pathMaterial);
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidth, unsigned int screenHeight);
private:
	void CheckShaderErrors(GLuint shader, string type);
};

#endif // !_GRAPHIC_HANDLER_
