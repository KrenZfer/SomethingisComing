#include "Tree.h"

Tree::Tree(){
	this->radius = 3.0f;
	once = false;
}

Tree::Tree(char* pathObj, char* pathMaterial) {
	this->graphHandler = GraphicHandler();
	this->pathObj = pathObj;
	this->pathMaterial = pathMaterial;
	this->radius = 1.0f;
	once = false;
	pos = vec3(0.0f, 2.0f, 0.0f);
}

Tree::~Tree(){
}

void Tree::BuildObject() {
	graphHandler.BuildObject("object.vert", "object.frag", "Objek/tree.obj", "Objek/tree.png");
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Tree::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	pos = Position;
	this->charPosition += pos;
	this->cameraChar = camera;
	this->lightPosChar = lightPos;
	this->screenHeight = screenHeightchar;
	this->screenWidth = screenWidthchar;
	graphHandler.DrawObject(pos, this->cameraChar, this->lightPosChar, this->screenWidth, this->screenHeight);
	once = true;
	pos = vec3(0.0f);
}

void Tree::UpdateObject(Camera camera, vec3 lightPos){}