#ifndef _H_STATE_H_
#define _H_STATE_H_


#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "TextsHandler.h"
#include "GameStage.h"
#include "GraphicObject.h"
#include "InputHandling.h"

class GameStateManager;
class State {

public:
	State(GameStateManager * gsms) {
		this->gsm = gsms;
	}
	virtual ~State() = default;

	GameStateManager* gsm;
	unsigned int screenWidth, screenHeight;

	virtual void Init(unsigned int screenWidth, unsigned int screenHeight) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

protected:
	virtual void Input() = 0;
};

#endif // !_H_STATE_H_
