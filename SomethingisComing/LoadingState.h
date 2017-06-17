#ifndef _H_LOADING_STATE_H_
#define _H_LOADING_STATE_H_

#include "State.h"
#include "TextsHandler.h"
#include "GraphicObject.h"
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

	int counter;

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render();
	static int MyThread(void* data);
private:
	virtual void Input();
};

static GraphicObject * graphicObject = GraphicObject::getInstance();

#endif // !_H_LOADING_STATE_H_

