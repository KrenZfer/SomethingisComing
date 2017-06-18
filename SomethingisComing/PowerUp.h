#ifndef _H_POWER_UP_H_
#define _H_POWER_UP_H_

#include <GLM/glm.hpp>
#include "ObjectVoxel.h"

using namespace glm;

class PowerUp : public ObjectVoxel {

public:
	PowerUp(char* pathObject, char* pathMaterial);
	~PowerUp();
	float radius;
	vec3 Position;
	vec3 posTemp;

	bool deploy;
	bool once;

	void setPosition(vec3 Pos);
	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
};

#endif // !_H_POWER_UP_H_
