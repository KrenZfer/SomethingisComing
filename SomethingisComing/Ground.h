#ifndef _GROUND_H
#define _GROUND_H

#include "ObjectVoxel.h"

using namespace glm;

class Ground :
	public ObjectVoxel
{
public:
	Ground();
	Ground(char* pathOBJ, char* pathMaterial);
	~Ground();

	enum GroundState {
		WITHTREES,
		GHOSTSTREET
	};

	float widthx, widthz;
	vec3 pos;

	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
};

#endif // !_GROUND_H
