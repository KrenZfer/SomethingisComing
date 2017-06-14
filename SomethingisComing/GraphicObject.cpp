#include "GraphicObject.h"

GraphicObject::GraphicObject() : chara(Character("Objek/chr_man.objek","Objek/chr_man.png"))
{
	Init();
	lengthPlatform = vec2(2.0f, 10.0f);
	groundFactorx = 50;
	groundFactorz = 25;
	buildStageDone = false;
	randZ = 10;
	_groundList = vector<Ground>(
		static_cast<unsigned int>(
			lengthPlatform.x*lengthPlatform.y/2), 
			Ground("Objek/platform.objek","Objek/platform.png"));
	_groundGhostList = vector<Ground>(
		static_cast<unsigned int>(
			lengthPlatform.x*lengthPlatform.y / 2),
		Ground("Objek/platformghost.objek", "Objek/platformghost.png"));
	_fenceList = vector<Fence>(static_cast<unsigned int>(lengthPlatform.y + 2));
	_treeList = vector<Tree>(static_cast<unsigned int>(_groundList.size()*3));
	_ghostList = vector<Ghost>(static_cast<unsigned int>(1
		//_groundGhostList.size()*5
		), Ghost("Objek/ghost.objek","Objek/ghost.png"));
	_summonHelper = vector<SummonHelper>(_groundGhostList.size());
	itground = _groundList.begin();
	itfence = _fenceList.begin();
	ittree = _treeList.begin();
	itgroundghost = _groundGhostList.begin();
	itghost = _ghostList.begin();
}

GraphicObject::~GraphicObject(){
	_groundList.clear();
	_groundGhostList.clear();
	_fenceList.clear();
	_treeList.clear();
	_ghostList.clear();
}

void GraphicObject::Init() {
	posFence = vec3(-25.0f, 2.0f, 0.0f);
	posTree = vec3(0.0f,2.0f,0.0f);
}

void GraphicObject::BuildObjects() {
	percentComplete = 0;
	chara.BuildObject();
	while (!buildStageDone) {
		if (itground != _groundList.end()) {
			itground->BuildObject();
			++itground;
		}
		if (itgroundghost != _groundGhostList.end()) {
			itgroundghost->BuildObject();
			++itgroundghost;
		}
		if (itfence != _fenceList.end()) {
			itfence->BuildObject();
			++itfence;
		}
		if (ittree != _treeList.end()) {
			ittree->BuildObject();
			ittree->charPosition = posTree;
			++ittree;
		}
		if (itghost != _ghostList.end()) {
			itghost->BuildObject();
			++itghost;
		}
		if (
			itground == _groundList.end()
			&& itfence == _fenceList.end()
			&& ittree == _treeList.end()
			&& itgroundghost == _groundGhostList.end()
			&& itghost == _ghostList.end()
			) {
			buildStageDone = true;
		}
		percentComplete += ((float)(1.0f / _ghostList.size() * 100));
		cout << "Loading " << percentComplete << "%" << endl;
	}
	buildStageDone = false;
	itground = _groundList.begin();
	itfence = _fenceList.begin();
	ittree = _treeList.begin();
	itgroundghost = _groundGhostList.begin();
	itghost = _ghostList.begin();
}
int GraphicObject::Collision(void *ptr) {
	ittree = _treeList.begin();
	bool checkCollision = false;
	while (!checkCollision) {
		if (ittree != _treeList.end()) {
			if ((SDL_sqrtf(
				powf(chara.charPosition.x - ittree->charPosition.x, 2)
				+ powf(chara.charPosition.z - ittree->charPosition.z, 2)
			)
				<= (chara.radius + ittree->radius)
				)) {
				if (chara.charPosition.x < ittree->charPosition.x) {
					chara.xpos = -1;
				}
				else {
					chara.xpos = 1;
				}
				if (chara.charPosition.z < ittree->charPosition.z) {
					chara.zpos = -1;
				}
				else {
					chara.zpos = 1;
				}
			}
			ittree++;
		}
		if (ittree == _treeList.end()) {
			checkCollision = true;
		}
	}
	if ((chara.charPosition.x <= -groundFactorx / 2 + 2
			|| chara.charPosition.x >= groundFactorx*lengthPlatform.x - groundFactorx / 2 - 2)
		) {
		if (chara.charPosition.x < 0) {
			chara.xpos = 1;
		}
		else {
			chara.xpos = -1;
		}
	}
	return 0;
}
