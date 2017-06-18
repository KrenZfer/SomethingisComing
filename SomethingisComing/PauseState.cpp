#include "PauseState.h"
#include "GameStateManager.h"

PauseState::PauseState(GameStateManager * gsm) : State(gsm)
{
	graphic = GraphicObject::getInstance();
	input = InputHandling::getInstance();
	textcaution = "Do You Want Back To Main Menu";
	decision = true;

}

PauseState::PauseState(GameStateManager * gsm, string text) : State(gsm)
{
	graphic = GraphicObject::getInstance();
	input = InputHandling::getInstance();
	textcaution = "You're Dead Man";
	decision = false;
	posPointer = vec3(0.0f);
}

PauseState::~PauseState()
{
}

void PauseState::Init(unsigned int screenWidth, unsigned int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	cautionText.InitFont(30, FONTNAME);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void PauseState::Update(float deltaTime)
{
	Input();
}

void PauseState::Render()
{
	//graphic->Background.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	graphic->pointer2.DrawObject(posPointer, this->screenWidth, this->screenHeight);
	graphic->ButtonNo.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	graphic->ButtonYes.DrawObject(vec3(0.0f), this->screenWidth, this->screenHeight);
	if (decision) {
		cautionText.Render(textcaution
			, static_cast<GLfloat>(this->screenWidth / 2 - 200)
			, static_cast<GLfloat>(this->screenHeight - 200.0f)
			, 1.0f
			, vec3(1.0f)
			, this->screenWidth
			, this->screenHeight
		);
	}
	else {
		cautionText.Render(textcaution
			, static_cast<GLfloat>(this->screenWidth / 2 - 100)
			, static_cast<GLfloat>(this->screenHeight - 200.0f)
			, 1.0f
			, vec3(1.0f)
			, this->screenWidth
			, this->screenHeight
		);
	}
	posPointer = vec3(0.0f);
}

void PauseState::Input()
{
	if (input->IsKeyPressed(SDLK_a)) {
		if (chooseState > 0) {
			chooseState--;
			posPointer.x = -170.0f;
		}
		input->ReleaseKey(SDLK_a);
		cout << chooseState << endl;
	}
	if (input->IsKeyPressed(SDLK_d)) {
		if (chooseState < 1) {
			chooseState++;
			posPointer.x = 170.0f;
		}
		input->ReleaseKey(SDLK_d);
		cout << chooseState << endl;
	}
	if (input->IsKeyPressed(SDLK_RETURN)) {
		switch (chooseState)
		{
		case ChangeState::BACK:
			SDL_Delay(1000);
			if (decision) {
				gsm->pop();
			}
			else {
				gsm->pop();
				gsm->set(new PlayState(gsm));
			}
			break;
		case ChangeState::MAINMENU:
			SDL_Delay(1000);
			//gsm->pop();
			gsm->set(new MainMenuState(gsm));
			break;
		default:
			cout << "Error" << endl;
			break;
		}
	}
}
