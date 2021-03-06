// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using json = nlohmann::json;
using namespace std;

void readStateFile(string filePath, json& j);
void writeMoveFile(string filePath, int move);

EntityID strategize(Detect &d, json & j);
int MoveCloserTo(Detect d,int x, int y,json& j);
int MoveToSafety(Detect d, int x, int y, json& j);


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
	//Operation for Game Engine Data Retrieving Purposes
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

	json j;
	readStateFile(filePath, j);

	string PlayerKey = argv[1];

	//Initialize detection area, the Solution Set
	int radius = (5 + (Round(j) / 80));
	Detect d(PlayerKey, j,radius);

	//Select target to approach, the Selection Function
	EntityID target = strategize(d, j);

		//Debugging Purposes
		cout << "target = " << target.GetID() << "x,y = " << target.GetX() << "," << target.GetY() << std::endl;

	//determine move based on given target or situation, the Objective Function
	int move = 7;
	if (target.GetID() != "null") {
		if (target.GetID() == Bomb)
			move = 5;
		else if (target.GetID() == "MoveToSafety")
			//move = 1;
			move = MoveToSafety(d,target.GetX(),target.GetY(),j);
		else
			move = MoveCloserTo(d, target.GetX(), target.GetY(), j);
	}
	//Writing Operation to pass move to the Game Engine
	writeMoveFile(filePath,move);
	
	return 0;
}
/*!
@brief modified reading operation for game engine
*/
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

/*!
@brief modified writing operation for game engine
*/
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

/*!
@brief to determine what movement command to issue that leads player closer to given target
it moving closer leads to dangerous area, trigger bomb command is issued instead
@return game command number
*/
int MoveCloserTo(Detect d, int x, int y, json& j) {
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
			if (block(j, (d.GetX() + (dX / abs(dX))), d.GetY() , Entity) != IndestructibleWall) {
				if (dX > 0) 
					move = 3; //MoveRight
				else		
					move = 2; //MoveLeft
			} else if (dY == 0){
				if (block(j, d.GetX(), (d.GetY() + 1), Entity) != IndestructibleWall)
					move = 4;
				else
					move = 1;

			} else {
				if (dY > 0) {
					move = 4; //MoveDown
				}
				else if (dY < 0) {
					move = 1; //MoveUp
				}
			}
			
		}
		else {
			if (block(j, d.GetX() , (d.GetY() + (dY / abs(dY))), Entity) != IndestructibleWall) {
				if (dY > 0)
					move = 4; //MoveDown
				else 
					move = 1; //MoveUp
			}
			else if (dX == 0){
				if (block(j, d.GetX() + 1, d.GetY(), Entity) != IndestructibleWall)
					move = 3;
				else
					move = 2;
			}
			else {
				if (dX > 0) {
					move = 3; //MoveRight
				}
				else if (dX < 0){
					move = 2; //MoveLeft
				}
			}
		
	}
	//untuk mengecek apakah move command membawa player ke daerah radius bomb
	string s = d.IsAroundSafe();
	switch (move) {
	case 1:
		if (s[0] == '0') move = 6;
		break;
	case 2:
		if (s[1] == '0') move = 6;
		break;
	case 3:
		if (s[2] == '0') move = 6;
		break;
	case 4:
		if (s[3] == '0') move = 6;
		break;
	default:
		;
	}
	return move;
}


/*!
@brief to determine what movement command to issue that can leads the player outside the dangerous zone
@return game command number
*/
int MoveToSafety(Detect d, int x, int y, json& j) {
	int move = 7;
	bool found = false;
	//Implementasi movetosafety
	string s = d.IsAroundSafe();
	//Jika tidak ada safe zone di sekitar
	if (s == "0000") {
		int i = d.GetX(), k = d.GetY();
		while (k < (int)mapY(j) && !found && block(j, i, (k + 1), Entity) == "null" && !haveBomb(j,i,k+1))
		{
			if (d.IsAroundSafe(i, (k + 1)) != "0000") {
				found = true;
				move = 4;
			}
			else
				k++;
		}
		i = d.GetX();
		k = d.GetY();
		while (k > 0 && !found && block(j, i, k - 1, Entity) == "null" && !haveBomb(j, i, k - 1))
		{
			if (d.IsAroundSafe(i, (k - 1)) != "0000") {
				found = true;
				move = 1;
			}
			else
				k--;
		}
		i = d.GetX();
		k = d.GetY();
		while (i < (int)mapX(j) && !found && block(j, (i + 1), k, Entity) == "null" && !haveBomb(j, i+1, k))
		{
			if (d.IsAroundSafe((i + 1), k) != "0000") {
				found = true;
				move = 3;
			}
			else
				i++;
		}
		i = d.GetX();
		k = d.GetY();
		while (i > 0 && !found && block(j, (i - 1), k, Entity) == "null" && !haveBomb(j, i-1, k))
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
				move =  i+1;
				found = true;
			}
			else
				i++;
		}

	}
	return move;
}

/*!
@brief the function that select what target to approach if the player is in the safe zone
or to issue a danger warning to call MoveToSafety
@return a EntityID contains either target location or Situation code
	id = "Bomb"			-> PlaceBomb
	id = "MoveToSafety" -> MoveToSafety()
	id = "Center"		-> target the center of the map
	id = SuperPowerUp	-> target the SuperPowerUp
	id = BombBagPowerUp	-> target the nearest BombBagPowerUp	
	id = RadiusPowerUp	-> target the nearest RadiusPowerUp	
	id = DestructibleWall	-> target the nearest Destructible Wall
	note : the keywords without enclosing " " are the keywords defined in jsonreader.h
*/
EntityID strategize(Detect & d,json & j)
{
	int xCenter = ((mapX(j) + 1)/ 2);
	int yCenter = ((mapY(j) + 1)/ 2);
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
