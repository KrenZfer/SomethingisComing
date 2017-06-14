#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/vector_angle.hpp>
#include <unordered_map>

#include "InputHandling.h"

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

using namespace std;
using namespace glm;

enum class State { RUNNING, EXIT };
enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS };

namespace Engine {
	class Game
	{
	public:
		Game();
		~Game();
		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		InputHandling* handling;
		//// Input Handling
		//void PressKey(unsigned int keyID);
		//void ReleaseKey(unsigned int keyID);
		//void SetMouseCoords(float x, float y);
		///// Returns true if the key is held down
		//bool IsKeyDown(unsigned int keyID);
		///// Returns true if the key was just pressed
		//bool IsKeyPressed(unsigned int keyID);
		////getters
		//vec2 GetMouseCoords() const { return _mouseCoords; }
		////GameController and joystick
		//void onEventAxis(int axis, int value);
		//load .obj
		/*bool loadObject(const char* path, 
			vector <vec3> & out_vertices,
			vector <vec2> & out_uvs, 
			vector <vec3> & out_normals);
		GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void UseShader(GLuint program);*/
	protected:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		unsigned int screenWidth, screenHeight;

	private:
		unsigned int lastFrame = 0, last = 0, _fps = 0, fps = 0;
		float targetFrameTime = 0, timeScale;
		bool keyOnce;
		//list<int> releasePtr;
		State state;
		float GetDeltaTime();
		SDL_GameController* joystick;
		void GetFPS();
		void PollInput();
		void Err(string errorString);
		void LimitFPS();
		/*void CheckShaderErrors(GLuint shader, string type);*/

		// Input Handling
		/// Returns true if the key is held down
		/*bool WasKeyDown(unsigned int keyID);
		unordered_map<unsigned int, bool> _keyMap;
		unordered_map<unsigned int, bool> _previousKeyMap;
		vec2 _mouseCoords;*/
	};
}
#endif

