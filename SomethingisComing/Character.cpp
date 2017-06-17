#include "Character.h"

Character::Character(char* pathObj, char* pathMaterial) 
	{
	graphHandler = GraphicHandler();
	input = InputHandling::getInstance();
	this->pathObj = pathObj;
	this->pathMaterial = pathMaterial;
	walk = false;
	radius = 1.0f;
	defaultPos = vec3(15.0f,2.0f,20.0f);
	charPosition = defaultPos;
	Forward = vec3(0.0f, 0.0f, 1.0f);
	directChar = Direction::FRONT;
}

Character::~Character() {
}

void Character::BuildObject() {
	graphHandler.BuildObject("object.vert","object.frag",pathObj,pathMaterial);
	this->VAOChar = graphHandler.VAO;
	this->shaderChar = graphHandler.shader;
}

void Character::DrawObject(vec3 Position, Camera camera, vec3 lightPos, unsigned int screenWidthchar, unsigned int screenHeightchar) {
	cameraChar = camera;
	lightPosChar = lightPos;
	pos += Position;
	screenHeight = screenHeightchar;
	screenWidth = screenWidthchar;
	if (walk) {
		charPosition += pos;
	}
	//cout << charPosition.x << " : " << charPosition.z << endl;
	graphHandler.DrawObject(pos, cameraChar, lightPosChar, screenWidth, screenHeight);
	pos = vec3(0.0f);
	walk = true;
}

void Character::UpdateObject(Camera camera, vec3 lightPos) {
	cameraChar = camera;
	lightPosChar = lightPos;
}

int Character::calculateRotationFactor(Direction current, Direction goal) {
	if (current < goal) {
		return goal - current;
	}
	else {
		return -(current - goal);
	}
}

void Character::MoveCharacter(float deltaTime)
{
	int factor = 0;
	if (input->IsKeyPressed(AXIS_X_LEFT)
		||input->IsKeyPressed(SDLK_a)) {
		if (!(directChar == Direction::LEFT)) {
			factor = calculateRotationFactor(directChar, Direction::LEFT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED);
		directChar = LEFT;
	}
	if (input->IsKeyPressed(AXIS_X_RIGHT)
		|| input->IsKeyPressed(SDLK_d)) {
		if (!(directChar == Direction::RIGHT)) {
			factor = calculateRotationFactor(directChar, Direction::RIGHT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED);
		directChar = RIGHT;
	}
	if (input->IsKeyPressed(AXIS_Y_UP)
		|| input->IsKeyPressed(SDLK_w)) {
		if (!(directChar == FRONT)) {
			factor = calculateRotationFactor(directChar, Direction::FRONT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED);
		directChar = FRONT;
	}
	if ((input->IsKeyPressed(AXIS_Y_DOWN)
		|| input->IsKeyPressed(SDLK_s)) && charPosition.z >= defaultPos.z) {
		if (!(directChar == Direction::BACK)) {
			factor = calculateRotationFactor(directChar, Direction::BACK);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED);
		directChar = BACK;
	}
	if ((input->IsKeyPressed(BTN_RECTANGLE))) {
		cout << charPosition.x << ", " << charPosition.z << endl;
	}
}