#include "GameStateManager.h"
#include "State.h"

GameStateManager::GameStateManager() {
	states = vector<unique_ptr<State>>();
}
GameStateManager::~GameStateManager() {}

void GameStateManager::push(State* state) {
	states.push_back(unique_ptr<State>(state));
	Init();
}

void GameStateManager::push(State * state, int data)
{
	states.push_back(unique_ptr<State>(state));
}

void GameStateManager::pop() {
	states.pop_back();
}

void GameStateManager::set(State* state) {
	states.pop_back();
	states.push_back(unique_ptr<State>(state));
	Init();
}

void GameStateManager::Init() {
	states.back().get()->Init(screenWidth, screenHeight);
}

void GameStateManager::Update(float deltaTime) {
	states.back().get()->Update(deltaTime);
}

void GameStateManager::Render() {
	states.back().get()->Render();
}