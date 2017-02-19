// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using json = nlohmann::json;
using namespace std;

void readStateFile(string filePath, json& j);
void writeMoveFile(string filePath, int move);
int Strategy(Detect d,int x, int y,json& j);
int MoveToSafety(Detect d, int x, int y, json& j);
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

	string PlayerKey = argv[1];

	Detect d(PlayerKey, j,5);
	EntityID target = strategize(d, j);
	if (target.GetID() != "null") {
		if (target.GetID() == Bomb)
			move = 5;
		else if (target.GetID() == "MoveToSafety")
			move = 1;
			//move = MoveToSafety(d,target.GetX(),target.GetY(),j);
		else
			move = Strategy(d, target.GetX(), target.GetY(), j);
	}
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

int Strategy(Detect d, int x, int y, json& j) {
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
	int dX = x - d.GetX(), dY = y - d.GetY();
	//Add strategy lain di atas ini
		//Jalankan kode di bawah jika disekitar player tidak ada entity atau indestructiblewall
		if (abs(dX) > abs(dY)) {
			if (block(j, (d.GetX() + (dX / abs(dX)) ), d.GetY() , Entity) != IndestructibleWall) {
				if (dX > 0) {
					move = 3; //MoveRight
				}
				else {
					if (dX < 0)
						move = 2; //MoveLeft
				}
			}
			else {
				if (dY > 0) {
					move = 4; //MoveDown
				}
				else {
					if (dY < 0)
						move = 1;  //MoveUp
				}
			}
		}
		else {
			if (block(j, d.GetX() , (d.GetY() + (dY / abs(dY) )), Entity) != IndestructibleWall) {
				if (dY > 0) {
					move = 4; //MoveDown
				}
				else {
					if (dY < 0)
						move = 1; //MoveUp
				}
			}
			else {
				if (dX > 0) {
					move = 3; //MoveRight
				}
				else {
					if (dX < 0)
						move = 2; //MoveLeft
				}
			}
		
	}
	return move;
}

int MoveToSafety(Detect d, int x, int y, json& j) {
	int move = 7;
	bool found = false;
	//Implementasi movetosafety
	string s = d.IsAroundSafe();
	//Jika tidak ada safe zone di sekitar
	if (s == "0000") {
		int i = d.GetX(), k = d.GetY();
		while (k < (int)mapY(j) && !found && block(j, i, k + 1, Entity) == "null" && !haveBomb(j,i,k+1))
		{
			if (d.IsAroundSafe(i, (k + 1)) != "0000") {
				found = true;
				move = 4;
			}
			else
				k++;
		}
		while (k > 0 && !found && block(j, i, k - 1, Entity) == "null" && !haveBomb(j, i, k - 1))
		{
			if (d.IsAroundSafe(i, (k - 1)) != "0000") {
				found = true;
				move = 1;
			}
			else
				k--;
		}
		while (i < (int)mapX(j) && !found && block(j, i + 1, k, Entity) == "null" && !haveBomb(j, i+1, k))
		{
			if (d.IsAroundSafe((i + 1), k) != "0000") {
				found = true;
				move = 3;
			}
			else
				i++;
		}
		while (i > 0 && !found && block(j, i - 1, k, Entity) == "null" && !haveBomb(j, i-1, k))
		{
			if (d.IsAroundSafe((i - 1), k) != "0000") {
				found = true;
				move = 2;
			}
			else
				i--;
		}
	}
	else {
		int i = 0;
		while (i < 4 && !found)
		{
			if (s[i] == '1') {
				move = i + 1;
				found = true;
			}
			else
				i++;
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
		if (d.IsDestructibleAdjacent()) {
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
		eOut.Set("MoveToSafety", xCenter, yCenter);
	}
	return eOut;
}
