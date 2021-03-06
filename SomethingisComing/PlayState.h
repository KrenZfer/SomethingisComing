#ifndef _H_PLAY_STATE_H
#define _H_PLAY_STATE_H

#include "State.h"
#include "PauseState.h"
#include <SDL/SDL.h>

using namespace glm;

class PlayState 
	: public State {

public:
	PlayState(GameStateManager * gsm);
	~PlayState();

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render();

private:
	GLuint VBO, VAO, EBO, texture, program, light, lamp, object;
	GLuint VAOLight, VAOObject;
	mat4 model, view, projection;
	Camera camera;
	vec3 cameraPos, lightPos, cameraEye;
	vec3 color, lightcolor;
	GLfloat yaw, pitch;
	TextstHandler textHandler;
	//singleton pointer
	GraphicObject * graphic;
	InputHandling* handling;
	//Game Stage
	GameStage stage;
	string text;
	bool mode;
	float xpos = 0, zpos = 0, ypos = 0,
		xposlight = 0, zposlight = 0;
	float cameraSpeed = 0.002f;

	virtual void Input();
	void UpdateSprite(float deltaTime);
	void MoveCamera(float deltaTime);
	void DrawLight();
	void BuildLight();


};

#endif // !_H_PLAY_STATE_H
