#pragma once
#include "Ghost.h"

Ghost::Ghost(char* pathObject, char* pathMaterial) {
	this->pathObj = pathObject;
	this->pathMaterial = pathMaterial;
	graphHandler = GraphicHandler();
	defaultPos = vec3(100.0f, 2.0f, 0.0f);
	pos = defaultPos;
	currentPos = defaultPos;
	forward = vec3(-1.0f, 0.0f, 0.0f);
	summon = false;
}

Ghost::~Ghost(){}

void Ghost::BuildObject() {
	graphHandler.BuildObject("object.vert", "object.frag", this->pathObj, this->pathMaterial);
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Ghost::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	this->cameraChar = camera;
	this->pos = Position;
	this->pos += tempPos;
	this->currentPos += pos;
	this->lightPosChar = lightPos;
	this->screenWidth = screenWidthchar;
	this->screenHeight = screenHeightchar;
	graphHandler.DrawObject(pos, this->cameraChar, this->lightPosChar, this->screenWidth, this->screenHeight);
}

void Ghost::MoveCharacter(float deltaTime) {
	if (summon) {
		tempPos += forward * 0.0007f;
	}
	if (summon && tempPos.x == 130) {
		summon = false;
		tempPos = vec3(0.0f);
		currentPos = defaultPos;
	}
}

void Ghost::flipY() {
	//masih harus dibenerin
	graphHandler.RMatrix = glm::rotate(graphHandler.RMatrix, 
		radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	//cout << forward.x << "," << forward.y << "," << forward.z << endl;
	forward = glm::rotate(forward, radians(180.0f), vec3(0.0f,1.0f,0.0f));
	//cout << forward.x << "," << forward.y << "," << forward.z << endl;
	defaultPos.x = -defaultPos.x + 50;
}

