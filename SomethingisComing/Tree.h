#ifndef _TREE_H
#define _TREE_H

#include "ObjectVoxel.h"

using namespace glm;

class Tree 
	: public ObjectVoxel
{

public:
	Tree();
	Tree(char* pathOBJ, char* pathMaterial);
	~Tree();

	vec3 pos;
	bool once;

	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
};

#endif // !_TREE_H
