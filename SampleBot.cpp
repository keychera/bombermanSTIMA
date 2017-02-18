// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using json = nlohmann::json;
using namespace std;

void readStateFile(string filePath, json& j);
void writeMoveFile(string filePath, int move);
int Strategy(Detect d,int x, int y,json& j);

EntityID strategize(Detect &d, json & j);

/* json tester
int main() {
	json j;
	ifstream infile("../state.json");
	infile >> j;
	string v = "John";
	cout << "hey" << endl;
	cout << (v == player(j,1,Name)) << endl;
	cout << v << endl;
	cout << player(j, 1, Key) << endl;
	cout << playerX(j,0) << endl;
	cout << playerY(j, 1) << endl;
	cout << (block(j, 0, 0, PowerUp) == IndestructibleWall) << endl;
	int i;
	cin >> i;
	return 0;
}
*/

int _tmain(int argc, _TCHAR* argv[])
{
	int move;
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

	json j;
	readStateFile(filePath, j);

	int xy = (j)["MapWidth"].get<int>();

	string PlayerKey = argv[1];

	Detect d(PlayerKey, j);
//	EntityID target = strategize(d, j);
//	if (target.GetID() != "null") {
//		if (target.GetID() != "Bomb")
			move = Strategy(d, 11, 11, j);
//		else
//		move = 5;
//	}
	writeMoveFile(filePath,move);
	return 0;
}

void readStateFile(string filePath,json& j)
{
	cout << "Reading state file " << filePath + "/" + "state.json" << std::endl;
	string fileContent;
	string line;
	ifstream myfile(filePath + "/" + "state.json");
	if (myfile.is_open())
	{
		myfile >> j;
	}
}

void writeMoveFile(string filePath,int move)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");

	if (outfile.is_open())
	{
		outfile << move << std::endl;
		outfile.close();
	}
}

int Strategy(Detect d,int x,int y,json& j) {
	/* Return move comamnd
	GAME COMMAND
	MoveUp = 1,
	MoveLeft = 2,
	MoveRight = 3,
	MoveDown = 4,
	PlaceBomb = 5,
	TriggerBomb = 6,
	DoNothing = 7
	*/
	
	/*	METHOD YANG BELUM DIIMPLEMETASI
		Detect.GetX() - Mengembalikan posisi x player
		Detect.GetY() - Mengembalikan posisi y player
	*/
	int move = 7; //cuma ada 1 return, jadi pakai integer 
	
	//Add strategy lain di atas ini
	int dX = x - d.GetX(), dY = y - d.GetY();
	if (abs(dX) > abs(dY)){
		if ( block(j, (d.GetX() -1 + (dX / abs(dX))), d.GetY()-1,Entity) != IndestructibleWall ){
			if (dX > 0) {
				move = 3; //MoveRight
			} 
			else if (dX < 0){
					move = 2; //MoveLeft
			}
		} else {
			if (dY > 0) {
				move = 4; //MoveDown
			}
			else if (dY < 0){
					move = 1;  //MoveUp
			}
		}
	} else {
		if ( block(j, d.GetY()-1, (d.GetY() + (dY / abs(dY) - 1)), Entity) != IndestructibleWall ) {
			
			if (dY > 0) {
				move = 4; //MoveDown
			}
			else if (dY < 0){
				move = 1; //MoveUp
			}
		} else {
			if (dX > 0) {
				move = 3; //MoveRight
			} 
			else if (dX < 0){
					move = 2; //MoveLeft
			}
		}
	}
	return move;
}

EntityID strategize(Detect & d,json & j)
{
	int xCenter = mapX(j) / 2;
	int yCenter = mapY(j) / 2;
	EntityID eOut("Center", xCenter, yCenter);
	if (d.IsSafe()) {
		string mark = d.IsAroundSafe();
		d.DetectAround(3);
		if (d.IsDestructibleAdjacent() && d.IsEscapePossible()){
			eOut.Set("Bomb", 0, 0);
		}
		else {
			eOut = d.IsSuperPowerUpAround();
			if (eOut.GetID() == "null") {
				eOut = d.IsPowerUpAround();
				if (eOut.GetID() == "null") {
					eOut = d.IsDestructibleAround();
					if (eOut.GetID() == "null") {
						eOut.Set("Center", xCenter, yCenter);
					}
				}
			}
		}
	} else {
		eOut.Set("MoveToSafety", 0, 0);
	}
	return eOut;
}
