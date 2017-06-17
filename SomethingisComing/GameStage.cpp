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
	numDefGhost = 0;
	posTempTree = 0.0f;
	graphic->posTree.x = 0.0f;
	graphic->posGhost.x = -30.0f;
	posTempGhost = graphic->groundFactorz * 2;
}

GameStage::~GameStage() {
}

void GameStage::DrawStage(Camera camera, vec3 lightPos, unsigned int screenWidth, unsigned int screenHeight) {
	int counter = 0;
	int counterFence = 0;
	int counterTree = 0;
	int counterGhost = 0;
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
	buildStageDone = false;
	int counterGround = 0;
	while (!buildStageDone) {
		counterSummon++;
		if (graphic->itground != graphic->_groundList.end() 
			|| graphic->itgroundghost != graphic->_groundGhostList.end()) {
			if ((counter >= graphic->lengthPlatform.x && !drawStageDone)) {
				graphic->posGround.z += graphic->groundFactorz;
				graphic->lastPosGround += graphic->groundFactorz;
				graphic->posGround.x = 0;
				counter = 0;
				lengthCounter++;
				counterGround++;
				if (changeGround) {
					limiterGround--;
					if (lengthCounter >= numGround) {
						changeGround = false;
						srand((unsigned int)counterSummon);
						numGroundGhost = rand() % 1 + 1;
						if (numGroundGhost >= limiterGroundGhost || limiterGround == 0) {
							numGroundGhost = limiterGroundGhost;
						}
						lengthCounter = 0;
					}
				} else {
					limiterGroundGhost--;
					if (lengthCounter >= numGroundGhost) {
						changeGround = true;
						srand((unsigned int)counterSummon*2);
						numGround = rand() % 1 + 1;
						if (numGround >= limiterGround) {
							numGround = limiterGround;
						}
						lengthCounter = 0;
					}
				}
				if (!changeGround) {
					spookyGround.push_back(counterGround);
					//cout << counterGround << endl;
				}
				else {
					ordinaryGround.push_back(counterGround);
				}
				itordinary = ordinaryGround.begin();
				itspooky = spookyGround.begin();
			}
			//fungsi untuk loop ground
			if (counter >= graphic->lengthPlatform.x) {
				graphic->lastPosGround += graphic->groundFactorz;
				counter = 0;
			}
			if ((graphic->itground != graphic->_groundList.end() || 
				graphic->itgroundghost != graphic->_groundGhostList.end()) 
				&& drawStageDone
				) {
				if (graphic->itground->charPosition.z < camera.Position.z - 100.0f) {
					graphic->posGround.z = graphic->lastPosGround + graphic->groundFactorz;
				}
				if (graphic->itgroundghost->charPosition.z < camera.Position.z - 100.0f) {
					graphic->posGround.z = graphic->lastPosGround + graphic->groundFactorz;
				}
			}
			//end
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
			if (drawStageDone) {
				graphic->posGround = vec3(0.0f);
			}
		}
		if (graphic->itfence != graphic->_fenceList.end()) {
			if (counterFence >= 2 && !drawStageDone) {
				graphic->posFence.z += graphic->groundFactorx;
				graphic->lastPosFence = graphic->posFence.z;
				graphic->posFence.x = -static_cast<float>(graphic->groundFactorz);
				counterFence = 0;
			}
			if (graphic->itfence != graphic->_fenceList.end() && drawStageDone) {
				if (graphic->itfence->charPosition.z + 50 < camera.Position.z) {
					graphic->posFence.z = static_cast<float>(graphic->lastPosFence + graphic->groundFactorx);
				}
			}
			if (counterFence >= graphic->lengthPlatform.x) {
				graphic->lastPosFence += graphic->groundFactorx;
				counter = 0;
			}
			graphic->itfence->DrawObject(graphic->posFence, camera, lightPos, screenWidth, screenHeight);
			if (!drawStageDone) {
				graphic->posFence.x += (graphic->lengthPlatform.x*graphic->groundFactorx);
				counterFence++;
			}
			++graphic->itfence;
			if (drawStageDone) {
				graphic->posFence = vec3(0.0f);
			}
		}
		
		if (graphic->ittree != graphic->_treeList.end() && graphic->itground == graphic->_groundList.end()) {
			numDefTree += 5;
			if (counterTree >=6 && itordinary != ordinaryGround.end()) {
				if (!drawStageDone) {
					posTempTree = static_cast<float>((*itordinary) * graphic->groundFactorz) - 10;
					graphic->LastPosTree = posTempTree;
					graphic->posTree.z = posTempTree;
					graphic->posTree.x = -15;
					counterTree = 0;
					numDefTree = 0;
					++itordinary;
				}
			}
			if (drawStageDone && graphic->ittree->charPosition.z < camera.Position.z -10) {
				//cout << "masuk" << endl;
				graphic->posTree.z = (graphic->lengthPlatform.y*graphic->groundFactorz);
				//graphic->posTree.x = -5;
			}
			graphic->ittree->DrawObject(graphic->posTree, camera, lightPos, screenWidth, screenHeight);
			if (!drawStageDone) {
				srand((unsigned int)counterSummon);
				graphic->posTree.z = posTempTree;
				graphic->posTree.z += (rand() % 20);
				srand((unsigned int)counterSummon*2);
				graphic->posTree.x += (rand() % (40 - numDefTree)) + (numDefTree/5);
				counterTree++;
			}
			else {
				graphic->posTree = vec3(0.0f);
			}
			++graphic->ittree;
		}
		if (graphic->itghost != graphic->_ghostList.end() && graphic->itgroundghost == graphic->_groundGhostList.end()) {
			numDefGhost += 6;
			if (counterGhost >= 6 && itspooky != spookyGround.end()) {
				if (!drawStageDone) {
					++itspooky;
					posTempGhost = static_cast<float>((*itspooky) * graphic->groundFactorz);
					graphic->lastPosGhost = posTempGhost;
					graphic->posGhost.z = posTempGhost;
					graphic->posGhost.x = -15.0f;
					counterGhost = 0;
					numDefGhost = 0;
				}
			}
			if (drawStageDone && graphic->itghost->currentPos.z < camera.Position.z - 50) {
				srand((unsigned int)counterSummon / 3);
				graphic->itghost->speed = static_cast<float>((rand() % 7) + 5) * 0.001f;
				graphic->posGhost.z = (graphic->lengthPlatform.y*graphic->groundFactorz);
			}
			graphic->itghost->DrawObject(graphic->posGhost, camera, lightPos, screenWidth, screenHeight);
			if (drawStageDone) {
				graphic->posGhost = vec3(0.0f);
			}
			if (!drawStageDone) {
				srand((unsigned int)counterSummon / 2 + 5);
				graphic->itghost->speed = static_cast<float>((rand() % 7)+4) * 0.002f;
				srand((unsigned int)counterSummon);
				graphic->posGhost.z = posTempGhost;
				graphic->posGhost.z += (rand() % 15);
				srand((unsigned int)counterSummon * 2/(counterSummon+4));
				graphic->posGhost.x += (rand() % (60 - numDefGhost)) + (numDefGhost / 3);
				counterGhost++;
			}
			++graphic->itghost;
		}
		if (
			graphic->itground == graphic->_groundList.end()
			&& graphic->itfence == graphic->_fenceList.end()
			&& graphic->ittree == graphic->_treeList.end()
			&& graphic->itgroundghost == graphic->_groundGhostList.end()
			&& graphic->itghost == graphic->_ghostList.end()
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