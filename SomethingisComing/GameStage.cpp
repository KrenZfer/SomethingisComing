#include "GameStage.h"

GameStage::GameStage()
{
	buildStageDone = false;
	drawStageDone = false;
	changeGround = true;
	graphic = GraphicObject::getInstance();
	posChara = graphic->chara.defaultPos;
	counterSummon = 0;
	numDefTree = 0;
	graphic->posTree.z = 10.0f;
	graphic->posTree.x = 0.0f;
}

GameStage::~GameStage() {
}

void GameStage::DrawStage(Camera camera, vec3 lightPos, unsigned int screenWidth, unsigned int screenHeight) {
	int counter = 0;
	int counterFence = 0;
	int counterTree = 0;
	int numGround = 2;
	int numGroundGhost = 1;
	int limiterGround = static_cast<int>(graphic->lengthPlatform.y / 2) - numGround;
	int limiterGroundGhost = static_cast<int>(graphic->lengthPlatform.y / 2) - numGroundGhost;
	int lengthCounter = 0;
	graphic->itground = graphic->_groundList.begin();
	graphic->itfence = graphic->_fenceList.begin();
	graphic->ittree = graphic->_treeList.begin();
	graphic->itgroundghost = graphic->_groundGhostList.begin();
	graphic->itghost = graphic->_ghostList.begin();
	//graphic->itsummon = graphic->_summonHelper.begin();
	buildStageDone = false;
	int counterGround = 0;
	while (!buildStageDone) {
		counterSummon++;
		if (graphic->itground != graphic->_groundList.end() 
			|| graphic->itgroundghost != graphic->_groundGhostList.end()) {
			if (counter >= graphic->lengthPlatform.x && !drawStageDone) {
				graphic->posGround.z += graphic->groundFactorz;
				graphic->posGround.x = 0;
				counter = 0;
				lengthCounter++;
				counterGround++;
				srand((unsigned int)time(NULL));
				if (changeGround) {
					limiterGround--;
					if (lengthCounter >= numGround) {
						changeGround = false;
						numGroundGhost = rand() % 2 + 1;
						if (numGroundGhost > limiterGroundGhost) {
							numGroundGhost = limiterGroundGhost;
						}
						lengthCounter = 0;
					}
				} else {
					limiterGroundGhost--;
					if (lengthCounter >= numGroundGhost) {
						changeGround = true;
						numGround = rand() % 2 + 1;
						if (numGround > limiterGround) {
							numGround = limiterGround;
						}
						lengthCounter = 0;
					}
				}
				if (!changeGround) {
					spookyGround.push_back(counterGround);
				}
				else {
					cout << counterGround << endl;
					ordinaryGround.push_back(counterGround);
				}
				itordinary = ordinaryGround.begin();
			}
			if ((changeGround && graphic->itground != graphic->_groundList.end()) || drawStageDone) {
				graphic->itground->DrawObject(graphic->posGround, camera, lightPos, screenWidth, screenHeight);
				++graphic->itground;
			}
			if ((!changeGround && graphic->itgroundghost != graphic->_groundGhostList.end()) || drawStageDone) {
				graphic->itgroundghost->DrawObject(graphic->posGround, camera, lightPos, screenWidth, screenHeight);
				++graphic->itgroundghost;
			}
			if (!drawStageDone) {
				graphic->posGround.x += graphic->groundFactorx;
				counter++;
			}
		}
		if (graphic->itfence != graphic->_fenceList.end()) {
			if (counterFence >= 2 && !drawStageDone) {
				graphic->posFence.z += graphic->groundFactorx;
				graphic->posFence.x = -static_cast<float>(graphic->groundFactorz);
				counterFence = 0;
			}
			graphic->itfence->DrawObject(graphic->posFence, camera, lightPos, screenWidth, screenHeight);
			if (!drawStageDone) {
				graphic->posFence.x += (graphic->lengthPlatform.x*graphic->groundFactorx);
				counterFence++;
			}
			++graphic->itfence;
		}
		if (graphic->ittree != graphic->_treeList.end() && graphic->itground == graphic->_groundList.end()) {
			numDefTree += 5;
			if (counterTree >=6 && !drawStageDone && itordinary != ordinaryGround.end()) {
				graphic->posTree.z = static_cast<float>((*itordinary) * graphic->groundFactorz) - 10;
				graphic->posTree.x = -10;
				counterTree = 0;
				numDefTree = 0;
				++itordinary;
			}
			graphic->ittree->DrawObject(graphic->posTree, camera, lightPos, screenWidth, screenHeight);
			if (!drawStageDone) {
				srand((unsigned int)counterSummon);
				graphic->posTree.z += (rand() % 20);
				graphic->posTree.x += (rand() % (40 - numDefTree)) + (numDefTree/5);
				counterTree++;
			}
			++graphic->ittree;
		}
		if (
			graphic->itground == graphic->_groundList.end()
			&& graphic->itfence == graphic->_fenceList.end()
			&& graphic->ittree == graphic->_treeList.end()
			&& graphic->itgroundghost == graphic->_groundGhostList.end()
			//&& graphic->itghost == graphic->_ghostList.end()
			) {
			buildStageDone = true;
		}
	}

	graphic->chara.DrawObject(posChara, camera, lightPos, screenWidth, screenHeight);

	drawStageDone = true;
	graphic->posGround = vec3(0.0f);
	graphic->posFence = vec3(0.0f);
	graphic->posTree = vec3(0.0f);
	graphic->posGhost = vec3(0.0f);
	posChara = vec3(0.0f);
}

void GameStage::Update(float deltaTime) {
	graphic->chara.MoveCharacter(deltaTime);
	graphic->itghost = graphic->_ghostList.begin();
	while (graphic->itghost != graphic->_ghostList.end()) {
		graphic->itghost->MoveCharacter(deltaTime);
		++graphic->itghost;
	}
}