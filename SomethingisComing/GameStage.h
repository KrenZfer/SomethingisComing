#ifndef _GAME_STAGE_
#define _GAME_STAGE_

#include <time.h>
#include "Tree.h"
#include "Ground.h"
#include "Fence.h"
#include "Character.h"
#include "GraphicObject.h"

class GameStage {

public:
	GameStage();
	~GameStage();

	GraphicObject * graphic;

	vec3 posGround;
	vec3 posFence;
	vec3 posTree;
	vec3 posChara;
	vec3 posGhost;
	vector<int> spookyGround;
	vector<int> ordinaryGround;
	bool buildStageDone;
	bool drawStageDone;
	bool drawCharacter;
	bool changeGround;

	int counterSummon;
	int numDefTree;

	vector<int>::iterator itordinary;
	vector<int>::iterator itspooky;
	

	void DrawStage(Camera camera, vec3 lightPos, unsigned int screenWidth, unsigned int screenHeight);
	void Update(float deltaTime);
};

#endif // !_GAME_STAGE_
