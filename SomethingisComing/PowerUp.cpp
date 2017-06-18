#include "PowerUp.h"

PowerUp::PowerUp(char* pathObject, char* pathMaterial) {
	Position = vec3(0.0f,2.0f,0.0f);
	radius = 1.0f;
	this->pathObj = pathObject;
	this->pathMaterial = pathMaterial;
	deploy = false;
	once = false;
}

PowerUp::~PowerUp(){}

void PowerUp::setPosition(vec3 Pos) {
	Position = Pos;
}

void PowerUp::BuildObject()
{
	graphHandler.BuildObject("object.vert", "object.frag", pathObj, pathMaterial);
	//graphHandler.SMatrix = scale(graphHandler.SMatrix, vec3(2.0f));
}

void PowerUp::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar)
{
	posTemp = Position;
	if (!once || !deploy) {
		this->Position += posTemp;
		posTemp = this->Position;
		cout << posTemp.x << " : " << posTemp.z << endl;
	}
	once = true;
	graphHandler.DrawObject(posTemp, camera, lightPos, screenWidthchar, screenHeightchar);
}

void PowerUp::UpdateObject(Camera camera, vec3 lightPos)
{
}
