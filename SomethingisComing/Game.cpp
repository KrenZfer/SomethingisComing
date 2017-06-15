#include "Game.h"


Engine::Game::Game()
{
	handling = InputHandling::getInstance();
}

InputHandling * InputHandling::_instance;

Engine::Game::~Game()
{

}

void Engine::Game::Start(string windowTitle, unsigned int screenWidth, unsigned int screenHeight, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale)
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//joystick init
	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
	SDL_GameControllerEventState(SDL_ENABLE);
	joystick = SDL_GameControllerOpen(0);
	int numJoy = SDL_NumJoysticks();
	if (joystick == nullptr) {
		cout << "joystick null : " << numJoy << endl;
	}
	else {
		cout << "Controller Name: " << SDL_GameControllerName(joystick) << endl;
	}
	/*SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);*/
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->timeScale = timeScale;

	if (targetFrameRate > 0) {
		targetFrameTime = 1000.0f / targetFrameRate;
	}


	Uint32 flags = SDL_WINDOW_OPENGL;

	if (WindowFlag::EXCLUSIVE_FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WindowFlag::FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (WindowFlag::BORDERLESS == windowFlag) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Setup SDL Window
	SDL_Window* window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (window == nullptr) {
		Err("Failed to create SDL window!");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		Err("Failed to create SDL_GL context!");
	}

	//Set up glew (optional but recommended)
	glewExperimental = GL_TRUE;
	GLenum glewStat = glewInit();
	if (glewStat != GLEW_OK) {
		Err("Failed to initialize glew!");
	}

	//Set VSYNC
	SDL_GL_SetSwapInterval(vsync);

	this->state = StateWindow::RUNNING;

	// Init delta time calculation
	last = SDL_GetTicks();
	//keyOnce = false;
	Init();

	//Will loop until we set _gameState to EXIT
	while (StateWindow::RUNNING == state) {
		float deltaTime = GetDeltaTime();
		GetFPS();
		PollInput();
		Update(deltaTime);
		Render();
		SDL_GL_SwapWindow(window);
		LimitFPS();

		//print only once every 60 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 60) {
			//cout << "FPS: " << fps << endl;
			frameCounter = 0;
		}
	}

	if (joystick != nullptr) {
		//SDL_JoystickClose(joystick);
		SDL_GameControllerClose(joystick);
		joystick = nullptr;
	}
}

float Engine::Game::GetDeltaTime()
{
	unsigned int time = SDL_GetTicks();
	unsigned int delta = time - lastFrame;
	lastFrame = time;

	return delta * timeScale;
}

void Engine::Game::GetFPS()
{
	if (SDL_GetTicks() - last > 1000) {
		fps = _fps;
		_fps = 0;
		last += 1000;
	}
	_fps++;
	//cout << "fps : " << fps << endl;
}

//Prints out an error message and exits the game
void Engine::Game::Err(string errorString)
{
	cout << errorString << endl;
	SDL_Quit();
	exit(1);
}

void Engine::Game::LimitFPS()
{
	//Limit the FPS to the max FPS
	SDL_Delay((Uint32)(targetFrameTime));

}

//void Engine::Game::CheckShaderErrors(GLuint shader, string type)
//{
//	GLint success;
//	GLchar infoLog[1024];
//	if (type != "PROGRAM")
//	{
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//			cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << endl;
//		}
//	}
//	else
//	{
//		glGetProgramiv(shader, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//			cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << endl;
//		}
//	}
//}
//
//GLuint Engine::Game::BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
//{
//	// 1. Retrieve the vertex/fragment source code from filePath
//	string vertexCode;
//	string fragmentCode;
//	string geometryCode;
//	ifstream vShaderFile;
//	ifstream fShaderFile;
//	ifstream gShaderFile;
//	// ensures ifstream objects can throw exceptions:
//	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
//	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
//	gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
//	try
//	{
//		// Open files
//		vShaderFile.open(vertexPath);
//		fShaderFile.open(fragmentPath);
//		stringstream vShaderStream, fShaderStream;
//		// Read file's buffer contents into streams
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//		// close file handlers
//		vShaderFile.close();
//		fShaderFile.close();
//		// Convert stream into string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//		// If geometry shader path is present, also load a geometry shader
//		if (geometryPath != nullptr)
//		{
//			gShaderFile.open(geometryPath);
//			stringstream gShaderStream;
//			gShaderStream << gShaderFile.rdbuf();
//			gShaderFile.close();
//			geometryCode = gShaderStream.str();
//		}
//	}
//	catch (ifstream::failure e)
//	{
//		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
//	}
//	const GLchar* vShaderCode = vertexCode.c_str();
//	const GLchar * fShaderCode = fragmentCode.c_str();
//	// 2. Compile shaders
//	GLuint vertex, fragment;
//	GLint success;
//	GLchar infoLog[512];
//	// Vertex Shader
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex, 1, &vShaderCode, NULL);
//	glCompileShader(vertex);
//	CheckShaderErrors(vertex, "VERTEX");
//	// Fragment Shader
//	fragment = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment, 1, &fShaderCode, NULL);
//	glCompileShader(fragment);
//	CheckShaderErrors(fragment, "FRAGMENT");
//	// If geometry shader is given, compile geometry shader
//	GLuint geometry;
//	if (geometryPath != nullptr)
//	{
//		const GLchar * gShaderCode = geometryCode.c_str();
//		geometry = glCreateShader(GL_GEOMETRY_SHADER);
//		glShaderSource(geometry, 1, &gShaderCode, NULL);
//		glCompileShader(geometry);
//		CheckShaderErrors(geometry, "GEOMETRY");
//	}
//	// Shader Program
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vertex);
//	glAttachShader(program, fragment);
//	if (geometryPath != nullptr)
//		glAttachShader(program, geometry);
//	glLinkProgram(program);
//	CheckShaderErrors(program, "PROGRAM");
//	// Delete the shaders as they're linked into our program now and no longer necessery
//	glDeleteShader(vertex);
//	glDeleteShader(fragment);
//	if (geometryPath != nullptr)
//		glDeleteShader(geometry);
//	return program;
//
//}
//
//void Engine::Game::UseShader(GLuint program)
//{
//	// Uses the current shader
//	glUseProgram(program);
//}
//
////objek loader
//bool Engine::Game::loadObject(const char* path,
//	vector <vec3> & out_vertices,
//	vector <vec2> & out_uvs,
//	vector <vec3> & out_normals) {
//	printf("Loading OBJ file %s...\n", path);
//
//	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
//	std::vector<glm::vec3> temp_vertices;
//	std::vector<glm::vec2> temp_uvs;
//	std::vector<glm::vec3> temp_normals;
//
//
//	FILE * file = fopen(path, "r");
//	//FILE * fil2 = fopen
//	if (file == NULL) {
//		printf("Impossible to open the file ! Are you in the right path ?\n");
//		getchar();
//		return false;
//	}
//
//	while (1) {
//
//		char lineHeader[128];
//		// read the first word of the line
//		int res = fscanf(file, "%s", lineHeader);
//		if (res == EOF)
//			break; // EOF = End Of File. Quit the loop.
//
//				   // else : parse lineHeader
//
//		if (strcmp(lineHeader, "v") == 0) {
//			glm::vec3 vertex;
//			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//			temp_vertices.push_back(vertex);
//		}
//		else if (strcmp(lineHeader, "vt") == 0) {
//			glm::vec2 uv;
//			fscanf(file, "%f %f\n", &uv.x, &uv.y);
//			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
//			temp_uvs.push_back(uv);
//		}
//		else if (strcmp(lineHeader, "vn") == 0) {
//			glm::vec3 normal;
//			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
//			temp_normals.push_back(normal);
//		}
//		else if (strcmp(lineHeader, "f") == 0) {
//			std::string vertex1, vertex2, vertex3;
//			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//			if (matches != 9) {
//				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
//				fclose(file);
//				return false;
//			}
//			vertexIndices.push_back(vertexIndex[0]);
//			vertexIndices.push_back(vertexIndex[1]);
//			vertexIndices.push_back(vertexIndex[2]);
//			uvIndices.push_back(uvIndex[0]);
//			uvIndices.push_back(uvIndex[1]);
//			uvIndices.push_back(uvIndex[2]);
//			normalIndices.push_back(normalIndex[0]);
//			normalIndices.push_back(normalIndex[1]);
//			normalIndices.push_back(normalIndex[2]);
//		}
//		else {
//			// Probably a comment, eat up the rest of the line
//			char stupidBuffer[1000];
//			fgets(stupidBuffer, 1000, file);
//		}
//
//	}
//
//	// For each vertex of each triangle
//	for (unsigned int i = 0; i<vertexIndices.size(); i++) {
//
//		// Get the indices of its attributes
//		unsigned int vertexIndex = vertexIndices[i];
//		unsigned int uvIndex = uvIndices[i];
//		unsigned int normalIndex = normalIndices[i];
//
//		// Get the attributes thanks to the index
//		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
//		glm::vec2 uv = temp_uvs[uvIndex - 1];
//		glm::vec3 normal = temp_normals[normalIndex - 1];
//
//		// Put the attributes in buffers
//		out_vertices.push_back(vertex);
//		out_uvs.push_back(uv);
//		out_normals.push_back(normal);
//
//	}
//	fclose(file);
//	return true;
//} 

// -------------- Input Handling --------------------

void Engine::Game::PollInput()
{
	SDL_Event evt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = StateWindow::EXIT;
			break;
		case SDL_KEYDOWN:
			//if (!keyOnce) {
			handling->PressKey(evt.key.keysym.sym);
				//cout << "lll" << endl;
			//}
			//handling->ReleaseKey(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			handling->ReleaseKey(evt.key.keysym.sym);
			//keyOnce = true;
			break;
		case SDL_JOYAXISMOTION:
			handling->onEventAxis(evt.jaxis.axis, evt.jaxis.value);
			break;
		case SDL_JOYBUTTONDOWN:
			handling->PressKey(evt.jbutton.button);
			break;
		case SDL_JOYBUTTONUP:
			handling->ReleaseKey(evt.jbutton.button);
			break;
		}
	}
}

//void Engine::Game::onEventAxis(int axis, int value) {
//	//bool isAxisLeft;
//	//int TOLERANCE = 8000;
//	//cout << "value : " << value << endl;
//	if (value < -TOLERANCE || value > TOLERANCE) {
//		if (axis == 0) {
//			if (value < -TOLERANCE) {
//				_keyMap[AXIS_X_LEFT] = true;
//				releasePtr.push_back(AXIS_X_LEFT);
//			}
//			else {
//				_keyMap[AXIS_X_RIGHT] = true;
//				releasePtr.push_back(AXIS_X_RIGHT);
//			}
//		}
//		if (axis == 1) {
//			if (value < -TOLERANCE) {
//				_keyMap[AXIS_Y_UP] = true;
//				releasePtr.push_back(AXIS_Y_UP);
//			}
//			else {
//				_keyMap[AXIS_Y_DOWN] = true;
//				releasePtr.push_back(AXIS_Y_DOWN);
//			}
//		}
//	}
//	if (value == -256) {
//		for (list<int>::iterator list_iter = releasePtr.begin();
//			list_iter != releasePtr.end(); list_iter++)
//		{
//			ReleaseKey(*list_iter);
//		}
//		releasePtr.clear();
//	}
//}
//
//void Engine::Game::PressKey(unsigned int keyID) {
//	// Here we are treating _keyMap as an associative array.
//	// if keyID doesn't already exist in _keyMap, it will get added
//	_keyMap[keyID] = true;
//	cout << "ID : " << keyID << endl;
//}
//
//void Engine::Game::ReleaseKey(unsigned int keyID) {
//	_keyMap[keyID] = false;
//}
//
//void Engine::Game::SetMouseCoords(float x, float y) {
//	_mouseCoords.x = x;
//	_mouseCoords.y = y;
//}
//
//bool Engine::Game::IsKeyDown(unsigned int keyID) {
//	// We dont want to use the associative array approach here
//	// because we don't want to create a key if it doesnt exist.
//	// So we do it manually
//	auto it = _keyMap.find(keyID);
//	if (it != _keyMap.end()) {
//		// Found the key
//		return it->second;
//	}
//	else {
//		// Didn't find the key
//		return false;
//	}
//}
//
//bool Engine::Game::IsKeyPressed(unsigned int keyID) {
//	// Check if it is pressed this frame, and wasn't pressed last frame
//	if (IsKeyDown(keyID) == true && WasKeyDown(keyID) == false) {
//		return true;
//	}
//	return false;
//}
//
//bool Engine::Game::WasKeyDown(unsigned int keyID) {
//	// We dont want to use the associative array approach here
//	// because we don't want to create a key if it doesnt exist.
//	// So we do it manually
//	auto it = _previousKeyMap.find(keyID);
//	if (it != _previousKeyMap.end()) {
//		// Found the key
//		return it->second;
//	}
//	else {
//		// Didn't find the key
//		return false;
//	}
//}




