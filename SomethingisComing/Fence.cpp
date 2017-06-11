#include "Fence.h"

Fence::Fence(){}

Fence::~Fence(){}

void Fence::BuildObject() {
	graphHandler.BuildObject("object.vert", "object.frag", "Objek/fence.obj", "Objek/fence.png");
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Fence::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	cameraChar = camera;
	lightPosChar = lightPos;
	charPosition = Position;
	screenHeight = screenHeightchar;
	screenWidth = screenWidthchar;
	graphHandler.DrawObject(charPosition, cameraChar, lightPosChar, screenWidth, screenHeight);
	//graphHandler.UseShader(this->shaderChar);
}

void Fence::UpdateObject(Camera camera, vec3 lightPos) {
	cameraChar = camera;
	lightPosChar = lightPos;
}