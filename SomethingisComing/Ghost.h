#pragma once
#ifndef _H_GHOST_H
#define _H_GHOST_H

#include "ObjectVoxel.h"

class Ghost : 
	public ObjectVoxel
{

public:
	Ghost(char* pathObject, char* pathMaterial);
	~Ghost();

	vec3 pos;
	vec3 defaultPos;
	vec3 forward;
	vec3 tempPos;
	float rotate;

	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
	void MoveCharacter(float deltaTime);
	void flipY();
};

#endif // !_H_GHOST_H
