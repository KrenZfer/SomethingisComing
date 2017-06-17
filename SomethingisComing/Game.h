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

#define FONTNAME "fonts/fixedsys-excelsior.ttf"
#define GAMENAME "SOMETHING'S COMING"

using namespace std;
using namespace glm;

enum class StateWindow { RUNNING, EXIT };
enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS };

namespace Engine {
	class Game
	{
	public:
		Game();
		~Game();
		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		InputHandling* handling;
	protected:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		unsigned int screenWidth, screenHeight;

	private:
		unsigned int lastFrame = 0, last = 0, _fps = 0, fps = 0;
		float targetFrameTime = 0, timeScale;
		bool keyOnce;
		StateWindow state;
		float GetDeltaTime();
		SDL_GameController* joystick;
		void GetFPS();
		void PollInput();
		void Err(string errorString);
		void LimitFPS();
	};
}
#endif

