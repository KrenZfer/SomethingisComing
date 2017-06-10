#include "Ground.h"

Ground::Ground(){}

Ground::Ground(char* pathOBJ, char* pathMaterial)
{
	graphHandler = GraphicHandler();
	this->pathObj = pathOBJ;
	this->pathMaterial = pathMaterial;
	this->widthx = 100;
	this->widthz = 50;
}

Ground::~Ground() {
}

void Ground::BuildObject() {
	graphHandler.BuildObject("object.vert", "object.frag", pathObj, pathMaterial);
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Ground::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	this->pos = Position;
	this->charPosition += pos;
	this->cameraChar = camera;
	this->lightPosChar = lightPos;
	this->screenHeight = screenHeightchar;
	this->screenWidth = screenWidthchar;
	graphHandler.DrawObject(pos, cameraChar, lightPosChar, screenWidth, screenHeight);
}

void Ground::UpdateObject(Camera camera, vec3 lightPos) {
	cameraChar = camera;
	lightPosChar = lightPos;
}