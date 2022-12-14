#include "People.h"

People::People() {
	loadImage(1);
	mX = mY = 0;
	alive = true;
}

People::People(int x, int y) {
	loadImage(1);
	mX = x;
	mY = y;
	alive = true;
}

People::~People() {

}

//******************************************//

int People::getmY(){
	return this->mY;
}

void People::setCoords(int x, int y) {
	mX = x;
	mY = y;
}

pair<int, int> People::getCoords() {
	return pair<int, int>(mX, mY);
}

void People::setVehicle(vector<Vehicle*>& vh) {
	g_vh = &vh;
}

void People::setAnimal(vector<Animal*>& an)
{
	g_an = &an;
}

//******************************************//

void People::loadImage(int type) {
	string file;
	image.clear();
	if (type == 1) {
		file = "ASCII\\life.txt";
		_height = 3;
		_width = 3;
	}
	if (type == 2) {
		file = "ASCII\\die.txt";
		_height = 3;
		_width = 5;
	}
	ifstream fin(file);
	string s;
	while (!fin.eof()) {
		getline(fin, s);
		image.push_back(s);
	}
}

void People::dieAnimation() {
	loadImage(2);
	while (mY > TOP_GAMEBOARD) {
		eraseFromScreen();
		mY -= 1;
		drawToScreen();
		Sleep(100);
	}
}

void People::drawToScreen() {
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}

void People::eraseFromScreen() {
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++)
			putchar(' ');
	}
}

void People::move() {
	int c = Common::getConsoleInput();
	if (c == 2 && mY > TOP_GAMEBOARD - 3) {
		eraseFromScreen();
		mY-=5;
		drawToScreen();
	}
	else if (c == 3 && mX > LEFT_GAMEBOARD + 1) {
		eraseFromScreen();
		mX--;
		drawToScreen();
	}
	else if (c == 5 && mY < TOP_GAMEBOARD + HEIGHT_GAMEBOARD) {
		eraseFromScreen();
		mY+=5;
		drawToScreen();
	}
	else if (c == 4 && mX < LEFT_GAMEBOARD + WIDTH_GAMEBOARD - 4) {
		eraseFromScreen();
		mX++;
		drawToScreen();
	}
}

//******************************************//

bool People::checkImpact() {
	vector<Vehicle*> v = *g_vh;
	vector<Animal*> a = *g_an;
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->getY() == mY - 1) {
			if (mX + _width >= v[i]->getX() && mX < v[i]->getX() + v[i]->getWidth()) {
				alive = false;
				return true;
			}
		}
	}

	for (int i = 0; i < a.size(); i++) {
		if (a[i]->getY() == mY - 1) {
			if (mX + _width >= a[i]->getX() && mX < a[i]->getX() + a[i]->getWidth()) {
				alive = false;
				return true;
			}
		}
	}

	return false;
}