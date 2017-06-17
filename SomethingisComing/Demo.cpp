#include "Demo.h"

Demo::Demo() 
	: gsm(GameStateManager())
{
	//gsm.push(new PlayState(&gsm));
	gsm.push(new LoadingState(&gsm));
}

Demo::~Demo()
{
}


void Demo::Init()
{
	gsm.screenWidth = screenWidth;
	gsm.screenHeight = screenHeight;
	gsm.Init();
}

void Demo::Update(float deltaTime)
{
	gsm.Update(deltaTime);
}

void Demo::Render()
{
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gsm.Render();
}

int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start(GAMENAME, 800, 600, true, WindowFlag::WINDOWED, 0, 1);

	return 0;
}