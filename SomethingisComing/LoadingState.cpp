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
	background = GraphicHandler();
	graphicObject = GraphicObject::getInstance();
}

GraphicObject * GraphicObject::_instance;

LoadingState::~LoadingState(){
}

//typedef struct {
//	vec3 color;
//} colors;
//
//int MyThread(void* colorText) {
//	float temp;
//	if (colorText.x >= 1.0f || colorText.x <= 0.0f) {
//		temp *= -1.0f;
//	}
//	colorText += temp;
//}

void LoadingState::Init(unsigned int screenWidth, unsigned int screenHeight) {
	graphicObject->Init();
	//std::thread buildThread()
	//background.BuildObject("Objek/Background.png");
	textTitle.InitFont(80, FONTNAME);
	textLoading.InitFont(20, FONTNAME);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	colorText = vec3(0.0f);
	temp = vec3(-0.007f);
	background.BuildObject("Objek/Sprite/Menu/Background.png");
	background.SMatrix = scale(background.SMatrix, vec3(2.0f));
	//thread = SDL_CreateThread(MyThread, "MyThread", ((void*)colorText));
}

void LoadingState::Update(float deltaTime) {
	graphicObject->BuildObjects();
	//if (counter == 1) {
	Loading = "LOADING";
		//counter = 0;
	//}
	Loading.append("  "+ to_string(static_cast<int>(graphicObject->percentComplete)) + "%");
	if (graphicObject->percentComplete >= 100.0f) {
		SDL_Delay(2000);
		gsm->set(new MainMenuState(gsm));
	}
	//counter++;
}

void LoadingState::Render() {
	background.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	textTitle.Render(TITLE
		, static_cast<GLfloat>(this->screenWidth / 2) - 360.0f
		, static_cast<GLfloat>(this->screenHeight / 2)
		, 1.0f
		, vec3(1.0f)
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