#include "MainMenuState.h"
#include "GameStateManager.h"

MainMenuState::MainMenuState(GameStateManager * gsm) : State(gsm), audio("Objek/Music/switch.wav")
{
	graphic = GraphicObject::getInstance();
	input = InputHandling::getInstance();
	TITLE = TextstHandler();
	textTitle = GAMENAME;
	once = true;
	audio.InitMusic();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Init(unsigned int screenWidth, unsigned int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	TITLE.InitFont(70, FONTNAME);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	posPointer = vec3(0.0f);
}

void MainMenuState::Update(float deltaTime)
{
	Input();
}

void MainMenuState::Render()
{
	graphic->Background.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	graphic->pointer.DrawObject(posPointer, this->screenWidth, this->screenHeight);
	graphic->ButtonPlay.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	graphic->ButtonCredit.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	graphic->ButtonExit.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	TITLE.Render(textTitle
		, static_cast<GLfloat>(this->screenWidth / 2 - 320)
		, static_cast<GLfloat>(this->screenHeight - 150.0f)
		, 1.0f
		, vec3(1.0f)
		, this->screenWidth
		, this->screenHeight
	);
	posPointer = vec3(0.0f);
}

void MainMenuState::Input()
{
	if (input->IsKeyPressed(SDLK_w)) {
		if (chooseState > 0) {
			chooseState--;
			posPointer.y = 100.0f;
			audio.PlayMusic(false);
		}
		input->ReleaseKey(SDLK_w);
		cout << chooseState << endl;
	}
	if (input->IsKeyPressed(SDLK_s)) {
		if (chooseState < 2) {
			chooseState++;
			posPointer.y = -100.0f;
			audio.PlayMusic(false);
		}
		input->ReleaseKey(SDLK_s);
		cout << chooseState << endl;
	}
	if (input->IsKeyRelease(SDLK_w)
		|| input->IsKeyRelease(SDLK_w)) {

	}
	if (input->IsKeyPressed(SDLK_RETURN)) {
		switch (chooseState)
		{
		case ChangeState::PLAY:
			SDL_Delay(1000);
			gsm->set(new PlayState(gsm));
			break;
		case ChangeState::CREDIT:
			cout << "Belum Buat CREDIT SCREEN";
			break;
		case ChangeState::EXIT:
			SDL_Quit();
			exit(0);
			break;
		default:
			cout << "Error" << endl;
			break;
		}
	}
}
