#ifndef _GROUND_H
#define _GROUND_H

#include "Game.h"
#include "Camera.h"
#include "GraphicHandler.h"
#include "ObjectVoxel.h"
#include <SOIL.h>
#include <SDL.h>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

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
