#include "Menu.h"


Menu::Menu() {
	game = nullptr;
	loadSettings();
}

Menu::~Menu() {
	saveSettings();
	delete game;
	game = nullptr;
}

//##################################################//

void Menu::printTitle()
{
	std::ifstream in("ASCII\\CrossRoad.txt");

	Common().setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);

	int left = 53, top = 4;
	int i = 0;
	while (!in.eof())
	{
		std::string s;
		getline(in, s);
		Common::gotoXY(left, top + i);
		std::cout << s;
		i++;
	}
	in.close();
}

void Menu::renderOptionsBox(int n)
{
	int boxW = 21, boxH = 2;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
	for (int i = 0; i < n; i++) {
		box = i * boxH;
		for (int j = 0; j < boxW; j++) {
			Common::gotoXY(left + j, top + box);
			putchar(205);
			Common::gotoXY(left + j, top + boxH + box);
			putchar(205);
		}

		for (int j = 0; j < boxH; j++) {
			Common::gotoXY(left, top + j + box);
			putchar(186);
			Common::gotoXY(left + boxW, top + j + box);
			putchar(186);
		}

		Common::gotoXY(left, top + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + box);
		putchar(185);
		Common::gotoXY(left, top + boxH + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + boxH + box);
		putchar(185);
	}
	Common::gotoXY(left, top);
	putchar(201);
	Common::gotoXY(left + boxW, top);
	putchar(187);
	Common::gotoXY(left, top + boxH * n);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * n);
	putchar(188);
}

void Menu::renderOptionsText(string text[], int left, int top)
{
	int width = 41;
	for (int i = 0; i < opt; i++) {
		Common::gotoXY((width - text[i].length()) / 2 + left, top + i * 2);
		std::cout << text[i];
	}
}

void Menu::renderArrowsOpt(const int& n) {
	int top = this->top + 1;
	int left = this->left - 3;
	Common::gotoXY(left, top + 2 * n);
	putchar(62);				//left arrows
	putchar(62);
	Common::gotoXY(left + 26, top + 2 * n);
	putchar(60);				//right arrows
	putchar(60);
}

//##################################################//

void Menu::ArrowUp(int slt) {
	int left = this->left - 3;
	int top = this->top + 1;

	Common::gotoXY(left, top + 2 * (slt + 1));
	cout << "  ";
	Common::gotoXY(left + 26, top + 2 * (slt + 1));
	cout << "  ";

	Common::gotoXY(left, top + 2 * slt);
	cout << ">>";
	Common::gotoXY(left + 26, top + 2 * slt);
	cout << "<<";
}

void Menu::ArrowDown(int slt) {
	int left = this->left - 3;
	int top = this->top + 1;

	Common::gotoXY(left, top + 2 * (slt - 1));
	cout << "  ";
	Common::gotoXY(left + 26, top + 2 * (slt - 1));
	cout << "  ";

	Common::gotoXY(left, top + 2 * slt);
	cout << ">>";
	Common::gotoXY(left + 26, top + 2 * slt);
	cout << "<<";
}

//##################################################//

void Menu::initMenu() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(opt);
	renderOptionsText(menuOptions, left - 9, top + 1);
	renderArrowsOpt(menuSlt);
}

void Menu::renderMenuScreen()
{
	t_sound = thread(&Menu::soundHandle, this);
	initMenu();
	renderMenuCurOpt();
	if (t_sound.joinable()) t_sound.join();
}

void Menu::renderMenuCurOpt()
{
	int c;
	bool loadMenu = true;
	while (loadMenu) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (menuSlt == 0) break;
			menuSlt--;
			ArrowUp(menuSlt);
			break;
		case 5:								//move down
			if (menuSlt == opt - 1) break;
			menuSlt++;
			ArrowDown(menuSlt);
			break;
		case 6:								//enter
			switch (menuSlt) {
			case 0:					//Play
				//gameHandle();
				renderPlayOptScreen();
				initMenu();
				break;
			case 1:					//Settings
				renderSettingScreen();
				initMenu();
				break;
			case 2:
				break;
			case 3:
				exitMenu = true;
				Common::clearConsole();
				return;
				break;
			}
		}
	}
}

//##################################################//

void Menu::initSettings() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(sett);
	renderOptionsText(settingsOptions, left - 9, top + 1);
	renderArrowsOpt(0);
}

void Menu::renderSettCurOpt() {
	int c, slt = 0;
	bool loadSett = true;
	while (loadSett) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:			//move up
			if (slt == 0) break;
			slt--;
			ArrowUp(slt);
			break;
		case 5:			//move down
			if (slt == sett - 1) break;
			slt++;
			ArrowDown(slt);
			break;
		case 6:			//enter
			switch (slt) {
			case 0:
				sound = !sound;
				break;
			case 1:
				return;
			}
			break;
		}
	}
}

void Menu::renderSettingScreen() {
	initSettings();
	renderSettCurOpt();
}

//##################################################//
void Menu::initPlayOpt() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(playOpt);
	renderOptionsText(playOptions, left - 9, top + 1);
	renderArrowsOpt(0);
}

void Menu::renderPlayOpt() {
	int c, slt = 0;
	bool loadPlayOpt = true;
	while (loadPlayOpt) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:			//move up
			if (slt == 0) break;
			slt--;
			ArrowUp(slt);
			break;
		case 5:			//move down
			if (slt == playOpt - 1) break;
			slt++;
			ArrowDown(slt);
			break;
		case 6:			//enter
			switch (slt) {
			case 0:
				delete game;
				runGame = true;
				game = new Game();
				Common::clearConsole();
				printTitle();
				game->inputName();
				game->runGame(1, "Data\\nhung.txt");
				runGame = false;
				loadPlayOpt = false;
				break;
			case 1:
				return;
			case 2:
				return;
			}
			break;
		}
	}
}

void Menu::renderPlayOptScreen() {
	initPlayOpt();
	renderPlayOpt();
}
//###############################################//

void Menu::soundHandle() {
	bool BgOff = false;
	mciSendString(L"open \"Sound/dumb_ways2die.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	setVolume(10);
	playBg();
	while (!exitMenu) {
		if (sound == true && BgOff == true) {
			playBg();
			BgOff = false;
		}
		else if (sound == false && BgOff == false) {
			stopBg();
			BgOff = true;
		}
	}
	stopBg();
}

void Menu::playBg() {
	mciSendString(L"play mp3 from 0 repeat", NULL, 0, NULL);
}

void Menu::stopBg() {
	mciSendString(L"stop mp3", NULL, 0, NULL);
}

void Menu::setVolume(int volume) {
	wstring cmd = L"setaudio mp3 volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

//##################################################//

void Menu::saveSettings() {
	ofstream out("settings.txt");

	out << sound;

	out.close();
}

void Menu::loadSettings() {
	ifstream in("settings.txt");

	in >> sound;

	in.close();
}

//##################################################//

void Menu::gameHandle() {
	delete game;
	game = new Game();
	runGame = true;

	t_game = thread(&Game::runGame, game);
	while (runGame) {
		if (Common::pressedKey(P)) {

		}
	}

	runGame = false;
	t_game.join();
}