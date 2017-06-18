#include "InputHandling.h"

InputHandling::InputHandling(){
	counter = 0;
	keyOnce = true;
}
InputHandling::~InputHandling(){}

void InputHandling::onEventAxis(int axis, int value) {
	//bool isAxisLeft;
	//int TOLERANCE = 8000;
	//cout << "value : " << value << endl;
	if (value < -TOLERANCE || value > TOLERANCE) {
		if (axis == 0) {
			if (value < -TOLERANCE) {
				_keyMap[AXIS_X_LEFT] = true;
				releasePtr.push_back(AXIS_X_LEFT);
			}
			else {
				_keyMap[AXIS_X_RIGHT] = true;
				releasePtr.push_back(AXIS_X_RIGHT);
			}
		}
		if (axis == 1) {
			if (value < -TOLERANCE) {
				_keyMap[AXIS_Y_UP] = true;
				releasePtr.push_back(AXIS_Y_UP);
			}
			else {
				_keyMap[AXIS_Y_DOWN] = true;
				releasePtr.push_back(AXIS_Y_DOWN);
			}
		}
	}
	if (value == -256) {
		for (list<int>::iterator list_iter = releasePtr.begin();
			list_iter != releasePtr.end(); list_iter++)
		{
			ReleaseKey(*list_iter);
		}
		releasePtr.clear();
	}
}

void InputHandling::PressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	_keyMap[keyID] = true;
}

void InputHandling::ReleaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;

}

void InputHandling::SetMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputHandling::IsKeyRelease(unsigned int keyID) {
	auto it = _pressedKey.find(keyID);
	bool temp;
	if (it != _pressedKey.end()) {
		// Found the key
		temp = it->second;
		_pressedKey[keyID] = false;
	}
	else {
		// Didn't find the key
		temp = false;
	}
	return temp;
}


bool InputHandling::IsKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool InputHandling::IsKeyPressed(unsigned int keyID) {
	// Check if it is pressed this frame, and wasn't pressed last frame
	if (IsKeyDown(keyID) == true && WasKeyDown(keyID) == false) {
		return true;
	}
	return false;
}

bool InputHandling::WasKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}