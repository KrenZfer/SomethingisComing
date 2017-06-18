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
	HP = 3;
	STAMINA = 3;
	DEAD = false;
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
	if (invincible > 0) {
		invincible--;
	}
	if (HP <= 0) {
		DEAD = true;
	}
	if (counterStamina >= 2000) {
		STAMINA--;
		counterStamina = 0;
	}
	counterStamina++;
	//cout << counterStamina << endl;
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

void Character::takeDamage() {
	if (invincible == 0) {
		HP--;
		cout << "Kena Damage : " << HP << endl;
		invincible = 100;
	}
}

void Character::staminaPowerUp()
{
	if (STAMINA < 3) {
		STAMINA++;
	}
	cout << "Tambah Stamina" << endl;
}

void Character::healthPowerUp()
{
	if (HP < 3) {
		HP++;
		cout << "Tambah HP" << endl;
	}
}

void Character::MoveCharacter(float deltaTime)
{
	if (charPosition.z < cameraChar.Position.z - 5) {
		HP = 0;
	}
	int factor = 0;
	if (input->IsKeyPressed(AXIS_X_LEFT)
		||input->IsKeyPressed(SDLK_a)) {
		if (!(directChar == Direction::LEFT)) {
			factor = calculateRotationFactor(directChar, Direction::LEFT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED) * static_cast<float>(STAMINA) / 3.0f;
		directChar = LEFT;
		cout << charPosition.z << endl;
	}
	if (input->IsKeyPressed(AXIS_X_RIGHT)
		|| input->IsKeyPressed(SDLK_d)) {
		if (!(directChar == Direction::RIGHT)) {
			factor = calculateRotationFactor(directChar, Direction::RIGHT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED) * static_cast<float>(STAMINA) / 3.0f;
		directChar = RIGHT;
		cout << charPosition.z << endl;
	}
	if (input->IsKeyPressed(AXIS_Y_UP)
		|| input->IsKeyPressed(SDLK_w)) {
		if (!(directChar == FRONT)) {
			factor = calculateRotationFactor(directChar, Direction::FRONT);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED) * static_cast<float>(STAMINA)/3.0f;
		directChar = FRONT;
		cout << charPosition.z << endl;
	}
	if ((input->IsKeyPressed(AXIS_Y_DOWN)
		|| input->IsKeyPressed(SDLK_s)) && charPosition.z >= defaultPos.z) {
		if (!(directChar == Direction::BACK)) {
			factor = calculateRotationFactor(directChar, Direction::BACK);
			graphHandler.RMatrix = rotate(graphHandler.RMatrix, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
			Forward = rotate(Forward, radians(factor*90.0f), vec3(0.0f, 1.0f, 0.0f));
		}
		pos += Forward * (SPEED) * static_cast<float>(STAMINA) / 3.0f;
		directChar = BACK;
		cout << charPosition.z << endl;
	}
	if ((input->IsKeyPressed(BTN_RECTANGLE))) {
		cout << charPosition.x << ", " << charPosition.z << endl;
	}
}