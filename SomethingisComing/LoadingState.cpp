#include "LoadingState.h"
#include "GameStateManager.h"

LoadingState::LoadingState(GameStateManager * gsm) 
	: State(gsm) 
	, textTitle(TextstHandler())
	, textLoading(TextstHandler())
	, thread(NULL)
{
	TITLE = GAMENAME;
	Loading = "LOADING";
}

LoadingState::~LoadingState(){
	SDL_DetachThread(thread);
}

GraphicObject * GraphicObject::_instance;

int LoadingState::MyThread(void* data) {
	graphicObject->BuildObjects();
	return static_cast<int>(graphicObject->percentComplete);
}

void LoadingState::Init(unsigned int screenWidth, unsigned int screenHeight) {
	graphicObject->Init();
	thread = SDL_CreateThread(MyThread, "MyThread", NULL);
	textTitle.InitFont(80, FONTNAME);
	textLoading.InitFont(20, FONTNAME);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	colorText = vec3(0.0f);
	temp = vec3(-0.01f);
}

void LoadingState::Update(float deltaTime) {
	if (colorText.x >= 1.0f || colorText.x <= 0.0f) {
		temp *= -1.0f;
	}
	colorText += temp;
	if (counter == 1) {
		Loading = "LOADING";
		counter = 0;
	}
	Loading.append("  "+ to_string(static_cast<int>(graphicObject->percentComplete)) + "%");
	counter++;
}

void LoadingState::Render() {
	textTitle.Render(TITLE
		, static_cast<GLfloat>(this->screenWidth / 2) - 360.0f
		, static_cast<GLfloat>(this->screenHeight / 2)
		, 1.0f
		, colorText
		, this->screenWidth
		, this->screenHeight
	);
	textLoading.Render(Loading
		, static_cast<GLfloat>(this->screenWidth) - 150.0f
		, static_cast<GLfloat>(25.0f)
		, 1.0f
		, vec3(1.0f)
		, this->screenWidth
		, this->screenHeight
	);
}

void LoadingState::Input() {

}