#ifndef _H_RECTANGLE_H
#define _H_RECTANGLE_H

#include <stdio.h>

using namespace std;

class Rectangle {

public:
	Rectangle(vec2);
	~Rectangle();

	int widthx;
	int widthy;
	int posx;
	int posz;
};

#endif // !_H_RECTANGLE_H
