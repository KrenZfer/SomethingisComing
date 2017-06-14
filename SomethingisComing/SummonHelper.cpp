#include "SummonHelper.h"

SummonHelper::SummonHelper(){
	summon = false;
	tempStart = 1;
}

SummonHelper::~SummonHelper(){}

void SummonHelper::SummonDecision(int currentFrame) {
	this->currentFrame = currentFrame;
	//cout << "masuk summon decision" << endl;
	srand((unsigned int)time(NULL));
	if (randFrame < 0) {
		randFrame = rand() % 20 + tempStart;
		summon = false;
	}
	if (this->currentFrame == randFrame) {
		randFrame = -3;
		summon = true;
	}
	tempStart = 15;
}

bool SummonHelper::isSummon() {
	return summon;
}
