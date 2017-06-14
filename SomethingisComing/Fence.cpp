#include "Fence.h"

Fence::Fence(){}

Fence::~Fence(){}

void Fence::BuildObject() {
	graphHandler.BuildObject("object.vert", "object.frag", "Objek/fence.objek", "Objek/fence.png");
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Fence::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	cameraChar = camera;
	lightPosChar = lightPos;
	pos += Position;
	charPosition += pos;
	screenHeight = screenHeightchar;
	screenWidth = screenWidthchar;
	graphHandler.DrawObject(pos, cameraChar, lightPosChar, screenWidth, screenHeight);
	pos = vec3(0.0f);
}

void Fence::UpdateObject(Camera camera, vec3 lightPos) {
	cameraChar = camera;
	lightPosChar = lightPos;
}