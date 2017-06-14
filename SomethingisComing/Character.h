#ifndef CHARACTER_H
#define CHARACTER_H

#include "ObjectVoxel.h"
#include "InputHandling.h"

using namespace glm;

#define SPEED 1.0f

class Character 
	: public ObjectVoxel
{
public :
	Character(char* pathObj, char* pathMaterial);
	~Character();

	enum Direction{ FRONT, RIGHT, BACK, LEFT };

	InputHandling * input;
	float xpos, zpos, ypos;
	bool walk;
	vec3 pos;
	vec3 defaultPos;
	Direction directChar = FRONT;
	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
	void MoveCharacter(float deltaTime);
};

#endif // !CHARACTER_H
