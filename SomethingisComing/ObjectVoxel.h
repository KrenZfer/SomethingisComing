#ifndef _OBJECT_VOXEL_H
#define _OBJECT_VOXEL_H

#include "Game.h"
#include "Camera.h"
#include "GraphicHandler.h"
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <string>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>

using namespace glm;

#define PI 3.14159265359f

class ObjectVoxel {

public:
	ObjectVoxel(){}
	~ObjectVoxel(){}

	vec3 charPosition;
	float radius;
	enum Drawing {DRAW, NONE};
	Drawing isDraw = Drawing::DRAW;
protected:
	GLuint VAOChar;
	GLuint shaderChar;
	Camera cameraChar;
	GraphicHandler graphHandler;
	vec3 lightPosChar;
	char* pathObj;
	char* pathMaterial;
	unsigned int screenWidth, screenHeight;
	virtual void BuildObject() {}
	virtual void DrawObject(vec3 Position, Camera camera, vec3 lightPos) {}
	virtual void UpdateObject(Camera camera, vec3 lightPos, unsigned int screenWidth, unsigned int screenHeight) {}
};

#endif // !_OBJECT_VOXEL_H
