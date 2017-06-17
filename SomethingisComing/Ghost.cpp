#pragma once
#include "Ghost.h"

Ghost::Ghost(char* pathObject, char* pathMaterial) {
	this->pathObj = pathObject;
	this->pathMaterial = pathMaterial;
	graphHandler = GraphicHandler();
	defaultPos = vec3(0.0f, 2.0f, 0.0f);
	pos = defaultPos;
	radius = 1.5f;
	currentPos = defaultPos;
	forward = vec3(-1.0f, 0.0f, 0.0f);
	speed = 0.007f;
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
	float rot = 0.0f;
	tempPos += forward * speed;
	//cout << tempPos.x << endl;
	if (tempPos.x >= 0.7f || tempPos.x <= -0.7f) {
		GhostRotate(180.0f);
		tempPos = vec3(0.0f);
	}
}

void Ghost::GhostRotate(float angle) {
	graphHandler.RMatrix = glm::rotate(graphHandler.RMatrix, 
	radians(angle), vec3(0.0f, 1.0f, 0.0f));
	forward = glm::rotate(forward, radians(angle), vec3(0.0f,1.0f,0.0f));
}

