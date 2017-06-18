#ifndef CHARACTER_H
#define CHARACTER_H

#include "ObjectVoxel.h"
#include "InputHandling.h"

using namespace glm;

#define SPEED 0.5f

class Character 
	: public ObjectVoxel
{
public :
	Character(char* pathObj, char* pathMaterial);
	~Character();

	enum Direction{ FRONT = 0, LEFT = 1, BACK = 2, RIGHT = 3};
	InputHandling * input;
	float xpos, zpos, ypos;
	bool walk;
	vec3 pos;
	vec3 defaultPos;
	vec3 Forward;
	int HP, STAMINA;
	int counterStamina;
	int invincible;
	Direction directChar = FRONT;
	int counterWalk;
	bool DEAD;
	void BuildObject();
	void DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar);
	void UpdateObject(Camera camera, vec3 lightPos);
	void MoveCharacter(float deltaTime);
	int calculateRotationFactor(Direction current, Direction goal);
	void takeDamage();
	void staminaPowerUp();
	void healthPowerUp();
};

#endif // !CHARACTER_H
