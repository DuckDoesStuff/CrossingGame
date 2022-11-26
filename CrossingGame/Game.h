#pragma once
#include <thread>
#include <mutex>
#include <unordered_map>
#include "Common.h"
#include "People.h"

#include "Car.h"
#include "Truck.h"
#include "Camel.h"
#include "Horse.h"

#define _numOfLane 5

class Game {
private:
	int level;
	int frame;
	bool out=false; //check out
	string name; //username
	vector<pair<int, int>> trafficLane;			//{index of first vh, timer}
	vector<int> trafficTimer;					//{timer}
	string* laneOpt;						//save lane

	int numOfObjs;
	People* human;
	vector<Vehicle*> vh;
	vector<Animal*> an;
public:
	Game();
	~Game();

	//******************************************//

	void runGame();
	void playGame(int);

	template <class T> 
	void initLane(vector<T*>&, T*, int, int, int, int);
	void initGameData(int);

	template <class T>
	void DrawObj(vector<T*>);

	void drawBoardGame();
	void drawPeople();
	void inputName();

	//******************************************//

	void updateVehicle();
	void updateAnimal();
	void setTraffic();
	void drawTraffic();

	//******************************************//
	//save game
	void saveGame();
	void savePosVehicle(ofstream&);
	void savePosAnimal(ofstream&);
	void saveLane(ofstream&);
	void quitGame();
	//******************************************//

	void setLevel(int n) { level = n; }
	int getLevel() { return level; }
};
