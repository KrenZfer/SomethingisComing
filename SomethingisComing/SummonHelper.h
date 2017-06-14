#ifndef _H_SUMMON_HELPPER_H
#define _H_SUMMON_HELPPER_H

#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

class SummonHelper {

public:
	SummonHelper();
	~SummonHelper();

	int randFrame;
	int currentFrame;
	bool summon;
	int tempStart;

	void SummonDecision(int currentFrame);
	bool isSummon();
};


#endif // !_H_SUMMON_HELPPER_H

