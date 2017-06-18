#ifndef _H_LOADING_STATE_H_
#define _H_LOADING_STATE_H_

#include "State.h"
#include "TextsHandler.h"
#include "GraphicObject.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <thread>
#include <SDL/SDL_thread.h>

class LoadingState
	: public State {

public:
	LoadingState(GameStateManager * gsm);
	~LoadingState();

	SDL_Thread *thread;

	TextstHandler textTitle;
	TextstHandler textLoading;

	string TITLE;
	string Loading;

	vec3 colorText;
	vec3 temp;

	GraphicHandler background;
	GraphicObject * graphicObject;

	int counter;

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render();
	void ThreadMe();
	//static int MyThread(void* data);
private:
	virtual void Input();
};

#endif // !_H_LOADING_STATE_H_

