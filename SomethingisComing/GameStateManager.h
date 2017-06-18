#ifndef _H_GAME_STATE_MANAGER_H_
#define _H_GAME_STATE_MANAGER_H_

#include <vector>
#include <memory>
//#include "State.h"

using namespace std;

class State;
class GameStateManager {

public:
	GameStateManager();
	~GameStateManager();

	vector<unique_ptr<State>> states;
	unsigned int screenWidth, screenHeight;

	void push(State* state);
	void push(State* state, int data);
	void pop();
	void set(State* state);
	void Init();
	void Update(float deltaTime);
	void Render();

};

#endif // !_H_GAME_STATE_MANAGER_H_
