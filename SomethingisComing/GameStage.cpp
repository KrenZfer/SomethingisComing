#include "GameStage.h"

GameStage::GameStage()
{
	buildStageDone = false;
	drawStageDone = false;
	drawCharacter = false;
	changeGround = true;
	graphic = GraphicObject::getInstance();
	posChara = graphic->chara.defaultPos;
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
	buildStageDone = false;
	while (!buildStageDone) {
		if (graphic->itground != graphic->_groundList.end() 
			|| graphic->itgroundghost != graphic->_groundGhostList.end()) {
			if (counter >= graphic->lengthPlatform.x && !drawStageDone) {
				graphic->posGround.z += graphic->groundFactorz;
				graphic->posGround.x = 0;
				counter = 0;
				lengthCounter++;
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
			}
			if ((changeGround && graphic->itground != graphic->_groundList.end()) || drawStageDone) {
				graphic->itground->DrawObject(graphic->posGround, camera, lightPos, screenWidth, screenHeight);
				++graphic->itground;
			}
			if ((!changeGround && graphic->itgroundghost != graphic->_groundGhostList.end()) || drawStageDone) {
				graphic->itgroundghost->DrawObject(graphic->posGround, camera, lightPos, screenWidth, screenHeight);
				if (graphic->itghost != graphic->_ghostList.end()) {
					int counter = 0;
					int factor = 1;
					for (; counter < 2 && graphic->itghost != graphic->_ghostList.end(); counter++) {
						if (!drawStageDone) {
							if (factor < 0) {
								graphic->itghost->flipY();
								//cout << graphic->itghost->defaultPos.x << "," << graphic->itghost->defaultPos.z << endl;
							}
							else {
								//cout << graphic->itghost->defaultPos.x << "," << graphic->itghost->defaultPos.z << endl;
							}
							graphic->posGhost = graphic->itghost->defaultPos;
							graphic->posGhost.z = graphic->posGround.z + (graphic->groundFactorz * factor / 4);
						}
						factor = -1;
						graphic->itghost->DrawObject(graphic->posGhost, camera, lightPos, screenWidth, screenHeight);
						++graphic->itghost;
					}
				}
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
				graphic->itfence->charPosition.x = graphic->posFence.x;
				graphic->itfence->charPosition.z = graphic->posFence.z;
				counterFence = 0;
			}
			graphic->itfence->DrawObject(graphic->posFence, camera, lightPos, screenWidth, screenHeight);
			if (!drawStageDone) {
				graphic->posFence.x += (graphic->lengthPlatform.x*graphic->groundFactorx);
				graphic->itfence->charPosition.x = graphic->posFence.x;
				counterFence++;
			}
			++graphic->itfence;
		}
		if (graphic->ittree != graphic->_treeList.end()) {
			if (!drawStageDone) {
				graphic->ittree->DrawObject(graphic->ittree->charPosition, camera, lightPos, screenWidth, screenHeight);
			}
			else {
				graphic->ittree->DrawObject(graphic->posTree, camera, lightPos, screenWidth, screenHeight);
			}
			++graphic->ittree;
		}
		if (
			graphic->itground == graphic->_groundList.end()
			&& graphic->itfence == graphic->_fenceList.end()
			&& graphic->ittree == graphic->_treeList.end()
			&& graphic->itgroundghost == graphic->_groundGhostList.end()
			) {
			buildStageDone = true;
		}
	}

	graphic->chara.DrawObject(posChara, camera, lightPos, screenWidth, screenHeight);

	drawCharacter = true;
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
	/*while (graphic->itghost != graphic->_ghostList.end()) {
		graphic->itghost->MoveCharacter(deltaTime);
		++graphic->itghost;
	}*/
}