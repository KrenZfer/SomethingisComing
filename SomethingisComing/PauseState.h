#ifndef _H_PAUSE_STATE_H_
#define _H_PAUSE_STATE_H_

#include "State.h"
#include "MainMenuState.h"

class PauseState : public State {
public:
	PauseState(GameStateManager * gsm);
	PauseState(GameStateManager * gsm, string text);
	~PauseState();

	InputHandling * input;

	enum ChangeState {
		MAINMENU = 0,
		BACK = 1
	};
	int chooseState = 0;
	bool once;
	bool decision;
	vec3 posPointer;

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Input();

	GraphicObject * graphic;
	TextstHandler cautionText;

	string textcaution;
};

#endif // !_H_PAUSE_STATE_H_
