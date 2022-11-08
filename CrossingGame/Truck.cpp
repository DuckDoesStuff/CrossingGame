﻿#include "Truck.h"

Truck::Truck(int type) {
	loadImage(type);
	mX = mY = 0;
	mSpeed = -1;
}

Truck::Truck(int type, int x, int y) {
	loadImage(type);
	mX = x + LEFT_GAMEBOARD + WIDTH_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	mSpeed = -1;
}

//******************************************//

void Truck::loadImage(int type)
{
	//Hình ảnh của obj
	string file;
	switch (type)
	{
	case 0:
		file = "ASCII\\truck1.txt";
		_height = 4;
		_width = 18;
		mSpeed = -1;
		break;
	case 1:
		file = "ASCII\\truck2.txt";
		_height = 4;
		_width = 12;
		mSpeed = -1;
		break;
	default:
		break;
	}
	ifstream in(file);
	
	string s;
	while (!in.eof()) {
		getline(in, s);
		image.push_back(s);
	}
	in.close();
}

//******************************************//

bool Truck::checkPos() {
	if ((mX + mSpeed) > LEFT_GAMEBOARD) return true;
	return false;
}

void Truck::updatePos()
{
	if (mX < WIDTH_GAMEBOARD - _width) eraseFromScreen();

	if (checkPos())
		mX += mSpeed;
	else
		mX = WIDTH_GAMEBOARD + _width;

	if (mX < WIDTH_GAMEBOARD - _width) drawToScreen();
}