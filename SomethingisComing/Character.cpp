#include "Character.h"

Character::Character(char* pathObj, char* pathMaterial) 
	{
	graphHandler = GraphicHandler();
	input = InputHandling::getInstance();
	this->pathObj = pathObj;
	this->pathMaterial = pathMaterial;
	walk = false;
	radius = 1.0f;
	defaultPos = vec3(0.0f,2.0f,20.0f);
	charPosition = defaultPos;
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
	pos = Position;
	screenHeight = screenHeightchar;
	screenWidth = screenWidthchar;
	if (walk) {
		pos.x = xpos;
		pos.z = zpos;
		charPosition += pos;
	}
	graphHandler.DrawObject(pos, cameraChar, lightPosChar, screenWidth, screenHeight);
	xpos = zpos = 0;
	walk = true;
}

void Character::UpdateObject(Camera camera, vec3 lightPos) {
	cameraChar = camera;
	lightPosChar = lightPos;
}

void Character::MoveCharacter(float deltaTime)
{
	if (input->IsKeyPressed(AXIS_X_LEFT)
		||input->IsKeyPressed(SDLK_a)) {
		/*if (!(directChar == LEFT)) {
			graphHandler.model = rotate(graphHandler.model, 90.0f, vec3(0.0f, 1.0f, 0.0f));
		}*/
		xpos += (SPEED);
		directChar = LEFT;
	}
	if (input->IsKeyPressed(AXIS_X_RIGHT)
		|| input->IsKeyPressed(SDLK_d)) {
		/*if (!(directChar == RIGHT)) {
			graphHandler.model = rotate(graphHandler.model, -90.0f, vec3(0.0f, 1.0f, 0.0f));
		}*/
		xpos -= (SPEED);
		directChar = RIGHT;
	}
	if (input->IsKeyPressed(AXIS_Y_UP)
		|| input->IsKeyPressed(SDLK_w)) {
		/*if (!(directChar == FRONT)) {
			graphHandler.model = rotate(graphHandler.model, 90.0f, vec3(0.0f, 1.0f, 0.0f));
		}*/
		zpos += (SPEED);
		directChar = FRONT;
	}
	if ((input->IsKeyPressed(AXIS_Y_DOWN)
		|| input->IsKeyPressed(SDLK_s)) && charPosition.z >= defaultPos.z) {
		/*if (!(directChar == BACK)) {
			graphHandler.model = rotate(graphHandler.model, -90.0f, vec3(0.0f, 1.0f, 0.0f));
		}*/
		zpos -= (SPEED);
		directChar = BACK;
	}
	if ((input->IsKeyPressed(BTN_RECTANGLE))) {
		cout << charPosition.x << ", " << charPosition.z << endl;
	}
}