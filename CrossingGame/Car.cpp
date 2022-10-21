#include "Car.h"

Car::Car()
{
	loadImage(0);
}

Car::Car(int type, int x, int y)
{
	loadImage(type);
	mX = x;
	mY = y;
}

void Car::drawToScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}

void Car::eraseFromScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++) {
			putchar(' ');
		}
	}
}

void Car::move()
{
	mX += mSpeed;
	drawToScreen();
}

void Car::loadImage(int type)
{
	string file;
	switch (type){
	case 0:
		file = "ASCII\\car1.txt";
		_height = 4;
		_width = 19;
	}

	ifstream fin(file);
	string s;
	while (!fin.eof()) {
		getline(fin, s);
		image.push_back(s);
	}

	fin.close();
}

void Car::updatePos()
{
	mX += mSpeed;
}
