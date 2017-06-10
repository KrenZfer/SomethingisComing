#ifndef _H_GRAPHIC_OBJECT_
#define _H_GRAPHIC_OBJECT_

#include "Tree.h"
#include "Ground.h"
#include "Fence.h"
#include "Character.h"
#include "Ghost.h"

class GraphicObject {

	static GraphicObject * _instance;

public:
	GraphicObject();
	~GraphicObject();

	void Init();
	void BuildObjects();
	int Collision(void *ptr);

	static GraphicObject* getInstance() {
		if (_instance == NULL) {
			_instance = new GraphicObject();
		}
		return _instance;
	}

	vector<Ground> _groundList;
	vector<Ground> _groundGhostList;
	vector<Fence> _fenceList;
	vector<Tree> _treeList;
	vector<Ghost> _ghostList;
	Character chara;

	vec3 posGround;
	vec3 posTree;
	vec3 posChara;
	vec3 posFence;
	vec3 posGhost;


	vec2 lengthPlatform;
	int groundFactorx, groundFactorz;
	int randZ;
	float percentComplete;

	bool buildStageDone;

	vector<Ground>::iterator itground;
	vector<Fence>::iterator itfence;
	vector<Tree>::iterator ittree;
	vector<Ground>::iterator itgroundghost;
	vector<Ghost>::iterator itghost;

	void setGrounds(vector<Ground> groundList) { _groundList = groundList; }
	void setFences(vector<Fence> fenceList) { _fenceList = fenceList; }
	void setTrees(vector<Tree> treeList) { _treeList = treeList; }
	vector<Ground> getGrounds() { return _groundList; }
	vector<Fence> getFences() { return _fenceList; }
	vector<Tree> getTrees() { return _treeList; }
};


#endif // !_H_GRAPHIC_OBJECT_
