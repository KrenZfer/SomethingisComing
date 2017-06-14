#ifndef _FENCE_H
#define _FENCE_H

#include "ObjectVoxel.h"

using namespace glm;

class Fence :
	public ObjectVoxel
{
public:
	Fence();
	~Fence();

	vec3 pos;

	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
};

#endif // !_FENCE_H