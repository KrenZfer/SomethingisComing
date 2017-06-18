#ifndef _H_MAIN_MENU_STATE_H_
#define _H_MAIN_MENU_STATE_H_

#include "State.h"
#include "PlayState.h"
#include "AudioHandling.h"

class MainMenuState : public State{
public:
	MainMenuState(GameStateManager * gsm);
	~MainMenuState();

	InputHandling * input;

	enum ChangeState {
		PLAY = 0,
		CREDIT = 1,
		EXIT = 2
	};
	int chooseState = 0;
	bool once;
	vec3 posPointer;

	AudioHandling audio;

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Input();

	GraphicObject * graphic;
	TextstHandler TITLE;

	string textTitle;
};

#endif // !_H_MAIN_MENU_STATE_H_
