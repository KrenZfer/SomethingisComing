#pragma once
#ifndef _H_INPUT_HANDLING_H_
#define _H_INPUT_HANDLING_H_

#include <GLM/glm.hpp>
#include <unordered_map>
#include <iostream>

using namespace glm;
using namespace std;

#define TOLERANCE 8000

#define BTN_TRIANGLE 0
#define BTN_ROUND 1
#define BTN_CROSS 2
#define BTN_RECTANGLE 3
#define BTN_LEFT_ONE 4
#define BTN_RIGHT_ONE 5
#define BTN_LEFT_TWO 6
#define BTN_RIGHT_TWO 7
#define AXIS_Y_UP 123
#define AXIS_Y_DOWN 145
#define AXIS_X_RIGHT 156
#define AXIS_X_LEFT 178

class InputHandling {
	static InputHandling * _instance;
public:
	InputHandling();
	~InputHandling();

	static InputHandling* getInstance() {
		if (_instance == NULL) {
			_instance = new InputHandling();
		}
		return _instance;
	}

	// Input Handling
	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	void SetMouseCoords(float x, float y);
	/// Returns true if the key is held down
	bool IsKeyDown(unsigned int keyID);
	/// Returns true if the key was just pressed
	bool IsKeyPressed(unsigned int keyID);
	bool IsKeyRelease(unsigned int keyID);
	//getters
	vec2 GetMouseCoords() const { return _mouseCoords; }
	//GameController and joystick
	void onEventAxis(int axis, int value);
	void countering();
	bool keyOnce;

private:
	list<int> releasePtr;

	// Input Handling
	/// Returns true if the key is held down
	bool WasKeyDown(unsigned int keyID);
	unordered_map<unsigned int, bool> _keyMap;
	unordered_map<unsigned int, bool> _previousKeyMap;
	unordered_map<unsigned int, bool> _pressedKey;
	vec2 _mouseCoords;
	int counter;
	unsigned int keyRelease;
};

#endif // !_H_INPUT_HANDLING_H_
