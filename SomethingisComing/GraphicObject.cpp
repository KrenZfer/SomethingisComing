#include "GraphicObject.h"

GraphicObject::GraphicObject() : chara(Character("Objek/chr_man.objek","Objek/chr_man.png"))
{
	Init();
	lengthPlatform = vec2(2.0f, 10.0f);
	groundFactorx = 50;
	groundFactorz = 25;
	buildStageDone = false;
	once = true;
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
	_ghostList = vector<Ghost>(static_cast<unsigned int>(
		_groundGhostList.size()*3
		), Ghost("Objek/ghost.objek","Objek/ghost.png"));
	_summonHelper = vector<SummonHelper>(_groundGhostList.size());
	_meatInterface = vector<GraphicHandler>(3);
	_healthInterface = vector<GraphicHandler>(3);
	_health3D = vector<PowerUp>(1, PowerUp("Objek/health.objek","Objek/health.png"));
	_meat3D = vector<PowerUp>(1, PowerUp("Objek/meat.objek", "Objek/meat.png"));
	itground = _groundList.begin();
	itfence = _fenceList.begin();
	ittree = _treeList.begin();
	itgroundghost = _groundGhostList.begin();
	itghost = _ghostList.begin();
	itmeatInterface = _meatInterface.begin();
	ithealthInterface = _healthInterface.begin();
	ithealth = _health3D.begin();
	itmeat = _meat3D.begin();
	percentComplete = 0;

}

GraphicObject::~GraphicObject(){
	/*_groundList.clear();
	_groundGhostList.clear();
	_fenceList.clear();
	_treeList.clear();
	_ghostList.clear();*/
}

void GraphicObject::Init() {
	posFence = vec3(-25.0f, 2.0f, 0.0f);
	posTree = vec3(0.0f,2.0f,0.0f);
	lastPosHealth = 500.0f;
	lastPosMeat = 600.0f;
	tambah = 0;
}

//diganti dengan loop diluar build sehingga tetap bisa menggambar loading screen
void GraphicObject::BuildObjects() {
	if (once) {
		chara.BuildObject();
		ButtonCredit.BuildObject("Objek/Sprite/Menu/credit.png");
		ButtonExit.BuildObject("Objek/Sprite/Menu/exit.png");
		ButtonPlay.BuildObject("Objek/Sprite/Menu/play.png");
		ButtonYes.BuildObject("Objek/Sprite/Pause/yes.png");
		ButtonNo.BuildObject("Objek/Sprite/Pause/no.png");
		Background.BuildObject("Objek/Sprite/Menu/Background.png");
		pointer.BuildObject("Objek/Sprite/Menu/pointer.png");
		pointer2.BuildObject("Objek/Sprite/Menu/pointer.png");

		Background.SMatrix = scale(Background.SMatrix, vec3(2.0f));
		ButtonNo.SMatrix = scale(ButtonNo.SMatrix, vec3(2.0f));
		ButtonYes.SMatrix = scale(ButtonYes.SMatrix, vec3(2.0f));
		pointer.SMatrix = scale(pointer.SMatrix, vec3(0.5f));
		pointer2.SMatrix = scale(pointer.SMatrix, vec3(0.7f));
		ButtonNo.TMatrix = translate(ButtonNo.TMatrix
			, vec3(ButtonNo.widthObject / 2 + 30, -10.0f, 0.0f));
		ButtonYes.TMatrix = translate(ButtonYes.TMatrix
			, vec3(-ButtonYes.widthObject / 2 - 30, -10.0f, 0.0f));
		ButtonPlay.SMatrix = scale(ButtonPlay.SMatrix, vec3(2.0f));
		ButtonCredit.SMatrix = scale(ButtonCredit.SMatrix, vec3(2.0f));
		Background.TMatrix = translate(Background.TMatrix, vec3(0.0f,0.0f,-1.0f));
		ButtonExit.SMatrix = scale(ButtonExit.SMatrix, vec3(2.0f));
		ButtonPlay.TMatrix = translate(ButtonPlay.TMatrix, vec3(0.0f, 20.0f, 0.0f));
		pointer.TMatrix = translate(ButtonPlay.TMatrix, vec3(-ButtonPlay.widthObject/2 - 40.0f, 0.0f, 0.0f));
		pointer2.TMatrix = translate(ButtonYes.TMatrix, vec3(-ButtonYes.widthObject / 2 - 40.0f, 0.0f, 0.0f));
		ButtonCredit.TMatrix = translate(ButtonPlay.TMatrix, vec3(0.0f, -ButtonPlay.heightObject - 30.0f, 0.0f));
		ButtonExit.TMatrix = translate(ButtonCredit.TMatrix, vec3(0.0f, -ButtonCredit.heightObject - 30.0f, 0.0f));
	}
	once = false;
	if (!buildStageDone) {
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
		if (itmeatInterface != _meatInterface.end()) {
			itmeatInterface->BuildObject("Objek/Sprite/Gameplay/stamina.png");
			++itmeatInterface;
		}
		if (ithealthInterface != _healthInterface.end()) {
			ithealthInterface->BuildObject("Objek/Sprite/Gameplay/health.png");
			++ithealthInterface;
		}
		if (itmeat != _meat3D.end()) {
			itmeat->BuildObject();
			++itmeat;
		}
		if (ithealth != _health3D.end()) {
			ithealth->BuildObject();
			++ithealth;
		}
		if (
			itground == _groundList.end()
			&& itfence == _fenceList.end()
			&& ittree == _treeList.end()
			&& itgroundghost == _groundGhostList.end()
			&& itghost == _ghostList.end()
			&& itmeatInterface == _meatInterface.end()
			&& ithealthInterface == _healthInterface.end()
			&& itmeat == _meat3D.end()
			&& ithealth == _health3D.end()
			) {
			buildStageDone = true;
		}
		percentComplete += ((float)(1.0f / _treeList.size() * 100));
		cout << "Loading " << percentComplete << "%" << endl;
	}
	else {
		buildStageDone = false;
		itground = _groundList.begin();
		itfence = _fenceList.begin();
		ittree = _treeList.begin();
		itgroundghost = _groundGhostList.begin();
		itghost = _ghostList.begin();
		itmeatInterface = _meatInterface.begin();
		ithealthInterface = _healthInterface.begin();
		ithealth = _health3D.begin();
		itmeat = _meat3D.begin();
	}
}
int GraphicObject::Collision(void *ptr) {
	ittree = _treeList.begin();
	itghost = _ghostList.begin();
	ithealth = _health3D.begin();
	itmeat = _meat3D.begin();
	bool checkCollision = false;
	while (!checkCollision) {
		if (ittree != _treeList.end()) {
			if ((SDL_sqrtf(
				powf(chara.charPosition.x - ittree->charPosition.x, 2)
				+ powf(chara.charPosition.z - ittree->charPosition.z, 2)
			)
				<= (chara.radius + ittree->radius - 0.3f)
				)) {
				if (chara.charPosition.x < ittree->charPosition.x) {
					chara.pos.x += -1;
				}
				else {
					chara.pos.x += 1;
				}
				if (chara.charPosition.z < ittree->charPosition.z) {
					chara.pos.z += -1;
				}
				else {
					chara.pos.z += 1;
				}
			}
			ittree++;
		}
		if (itghost != _ghostList.end()) {
			if ((SDL_sqrtf(
				powf(chara.charPosition.x - itghost->currentPos.x, 2)
				+ powf(chara.charPosition.z - itghost->currentPos.z, 2)
			)
				<= (chara.radius + itghost->radius - 0.3f)
				)) {
				//menabrak ghost atau melewatinya kehilangan HP
				chara.takeDamage();
			}
			++itghost;
		}
		if (itmeat != _meat3D.end()) {
			if ((SDL_sqrtf(
				powf(chara.charPosition.x - itmeat->Position.x, 2)
				+ powf(chara.charPosition.z - itmeat->Position.z, 2)
			)
				<= (chara.radius + itmeat->radius - 0.3f)
				)) {
				chara.staminaPowerUp();
				itmeat->deploy = false;
			}
			++itmeat;
		}
		if (ithealth != _health3D.end()) {
			if ((SDL_sqrtf(
				powf(chara.charPosition.x - ithealth->Position.x, 2)
				+ powf(chara.charPosition.z - ithealth->Position.z, 2)
			)
				<= (chara.radius + ithealth->radius - 0.3f)
				)) {
				chara.healthPowerUp();
				ithealth->deploy = false;
			}
			++ithealth;
		}
		if (ittree == _treeList.end()
			&& itghost == _ghostList.end()
			&& ithealth == _health3D.end()
			&& itmeat == _meat3D.end()) {
			checkCollision = true;
		}
	}
	if ((chara.charPosition.x <= -groundFactorx / 2 + 2
			|| chara.charPosition.x >= groundFactorx*lengthPlatform.x - groundFactorx / 2 - 2)
		) {
		if (chara.charPosition.x < 0) {
			chara.pos.x += 1;
		}
		else {
			chara.pos.x += -1;
		}
	}
	return 0;
}
