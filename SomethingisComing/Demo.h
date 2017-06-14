#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <string>
#include <SDL/SDL.h>

#include "Game.h"
#include "Camera.h"
#include "Character.h"
#include "Ground.h"
#include "Tree.h"
#include "GameStage.h"
#include "GraphicObject.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80

using namespace glm;

class Demo  :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
private:
	GLuint VBO, VAO, EBO, texture, program, light, lamp, object;
	GLuint VAOLight, VAOObject;
	GLuint buffervertexs, bufferuvs, buffernormals;
	mat4 model, view, projection;
	vec3 color, lightcolor;
	vec3 cameraPos, lightPos, cameraEye;
	GLfloat yaw, pitch;
	vector<vec3> verticesObject;
	vector<vec2> uvsObject;
	vector<vec3> normalsObject;
	Camera camera;
	SDL_Thread *thread;
	//singleton pointer
	GraphicObject * graphicObjects;
	//Character chara;
	GameStage stage;
	bool test;
	bool mode;
	float frame_dur = 0, frame_width = 0, 
		xpos = 0, zpos = 0, ypos = 0,
		xposlight = 0, zposlight = 0;
	unsigned int frame_idx = 0;
	void BuildSprite();
	void DrawSprite();
	//void ReColor();
	void UpdateSprite(float deltaTime);
	void MoveSprite(float deltaTime);
};
#endif

