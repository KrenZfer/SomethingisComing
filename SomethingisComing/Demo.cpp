#include "Demo.h"

Demo::Demo() 
	: graphicObjects(GraphicObject::getInstance())
	, gsm(GameStateManager())
{

}

GraphicObject * GraphicObject::_instance;

Demo::~Demo()
{
}


void Demo::Init()
{
	graphicObjects->Init();
	graphicObjects->BuildObjects();
	gsm.screenWidth = screenWidth;
	gsm.screenHeight = screenHeight;
	gsm.push(new PlayState(&gsm));
	gsm.Init();
	//playstate.Init(screenWidth, screenHeight);
}

void Demo::Update(float deltaTime)
{
	gsm.Update(deltaTime);
	//playstate.Update(deltaTime);
}

void Demo::Render()
{
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//playstate.Render();
	gsm.Render();
}

int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start("Draw Cube", 800, 600, true, WindowFlag::WINDOWED, 0, 1);

	return 0;
}