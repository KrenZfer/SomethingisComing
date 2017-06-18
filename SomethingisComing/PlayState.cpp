#include "PlayState.h"
#include "GameStateManager.h"

PlayState::PlayState(GameStateManager * gsm) 
	: cameraPos(-11.0f, 33.0f, 0.0f)
	, cameraEye(0.0f, 1.0f, 0.0f)
	, yaw(-298)
	, pitch(-44)
	, lightPos(10.0f, 30.0f, 30.0f)
	, stage(GameStage())
	, graphic(GraphicObject::getInstance())
	, textHandler(TextstHandler())
	, State(gsm)
{
	handling = InputHandling::getInstance();
}

PlayState::~PlayState() {

}

void PlayState::Init(unsigned int screenWidth, unsigned int screenHeight) {
	camera = Camera(cameraPos, cameraEye, yaw, pitch);
	glEnable(GL_DEPTH_TEST);
	mode = false;
	textHandler.InitFont(20, FONTNAME);
	//Setting viewport
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	xpos = cameraPos.x;
	zpos = cameraPos.z;
	ypos = cameraPos.y;
	xposlight = lightPos.x;
	zposlight = lightPos.z;
	//ypos = lightPos.y;
	yaw = camera.Yaw;
	pitch = camera.Pitch;
	color = vec3(0.3f, 0.8f, 0.7f);
	//Set the background color
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void PlayState::Update(float deltaTime) {
	Input();
	MoveCamera(deltaTime);
	stage.Update(deltaTime);
	UpdateSprite(deltaTime);
	graphic->Collision((void *)NULL);
}

void PlayState::Render() {
	text = "PRESS ESC TO PAUSE";

	//DrawSprite();
	stage.DrawStage(camera, lightPos, screenWidth, screenHeight);
	textHandler.Render(text, static_cast<GLfloat>(screenWidth / 2 - 90), static_cast<GLfloat>(screenHeight - 25), 1.0f, vec3(1.0f), screenWidth, screenHeight);
	mode = true;
}

void PlayState::Input() {

}

void PlayState::UpdateSprite(float deltaTime)
{
	camera.Position = cameraPos;
	//cout << camera.Position.x << " : " << camera.Position.z << endl;
	camera.Pitch = pitch;
	camera.Yaw = yaw;
	camera.updateCameraVectors();
	if (stage.graphic->chara.DEAD) {
		gsm->push(new PauseState(gsm, "You're A Dead Man!!!"));
	}
}

void PlayState::MoveCamera(float deltaTime)
{
	if ((handling->IsKeyPressed(AXIS_X_LEFT)
		|| handling->IsKeyPressed(SDLK_a))
		&& cameraPos.x <= 21
		) {
		xpos += (SPEED / 2);
		xposlight += (SPEED / 2);
	}
	if ((handling->IsKeyPressed(AXIS_X_RIGHT)
		|| handling->IsKeyPressed(SDLK_d))
		&& cameraPos.x >= -11
		) {
		xpos -= (SPEED / 2);
		xposlight -= (SPEED / 2);
	}
	if ((handling->IsKeyPressed(AXIS_Y_UP)
		|| handling->IsKeyPressed(SDLK_w))
		//&& false
		&& stage.graphic->chara.charPosition.z - camera.Position.z >= 25
		) {
		zpos += (SPEED);
		zposlight += (SPEED);
	}
	if ((handling->IsKeyPressed(AXIS_Y_DOWN)
		|| handling->IsKeyPressed(SDLK_s))
		&& cameraPos.z >= 0
		&& false
		) {
		zpos -= (SPEED / 2);
		zposlight -= (SPEED / 2);
	}
	if ((handling->IsKeyPressed(SDLK_ESCAPE))) {
		gsm->push(new PauseState(gsm));
	}
	if (handling->IsKeyPressed(BTN_CROSS)
		) {
		ypos -= (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_ROUND)
		) {
		ypos += (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_LEFT_ONE)) {
		yaw -= (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_LEFT_TWO)) {
		yaw += (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_RIGHT_ONE)) {
		pitch -= (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_RIGHT_TWO)) {
		pitch += (SPEED / 2);
	}
	if (handling->IsKeyPressed(BTN_TRIANGLE)) {
		cout << xpos << ", " << ypos << ", " << zpos << ", " << yaw << ", " << pitch << endl;
	}
	if (mode) {
	zpos += deltaTime * (cameraSpeed);
	zposlight += deltaTime * (cameraSpeed);
	}
	cameraPos.z = zpos;
	cameraPos.x = xpos;
	//cameraPos.y = ypos;
	//}
	//else {
	//lightPos.x = xposlight;
	lightPos.z = zposlight;
	//lightPos.y = ypos;
	//}
}

// DIJELASKAN
void PlayState::DrawLight() {

	//mengakifkan shader untuk objek lampu
	GraphicHandler().UseShader(this->lamp);

	// mengambil lokasi variabel uniform pada shader lamp
	GLint modelLoc = glGetUniformLocation(this->lamp, "model");
	GLint viewLoc = glGetUniformLocation(this->lamp, "view");
	GLint projLoc = glGetUniformLocation(this->lamp, "projection");

	view = camera.GetViewMatrix();
	projection = perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

	//mengisi variable uniform pada shader dengan nilai yang ditentukan
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	model = glm::mat4();
	model = translate(model, lightPos);
	//model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//menggambar objek lampu atau cahaya (sumber)
	glBindVertexArray(VAOLight);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

void PlayState::BuildLight()
{
	//membuat shader dan menginisialisasi lokasi shader
	this->light = GraphicHandler().BuildShader("lightShader.vert", "lightShader.frag");
	this->lamp = GraphicHandler().BuildShader("lampShader.vert", "lampShader.frag");

	//vertice untuk objek kubus
	GLfloat vertices[] = {
		//BELAKANG
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		//DEPAN
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		//KANAN
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		//KIRI
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		//BAWAH
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		//ATAS
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	//INISIALISASI AWAL VAO, VBO
	// menggenerate vertex array VAO untuk vertice objek kubus
	glGenVertexArrays(1, &VAO);
	//menggenerate vertex buffer
	glGenBuffers(1, &VBO);
	//membind buffer 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// BEGIN POINTER KE LIGHTSHADER
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal Vector
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// END
	glBindVertexArray(0);

	//
	glGenVertexArrays(1, &VAOLight);
	glBindVertexArray(VAOLight);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

