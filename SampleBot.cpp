// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using json = nlohmann::json;
using namespace std;

void readStateFile(string filePath);
void writeMoveFile(string filePath);

/* json tester
int main() {
	json j;
	ifstream infile("../state.json");
	infile >> j;
	string v = "John";
	cout << "hey" << endl;
	cout << (v == jason(j,player,1,Name)) << endl;
	cout << v;
	cout << jason(j, player, 1, Key) << endl;
	cout << jason(j, player, 0, Name) << endl;
	cout << jason(j, player, 1, BombBag) << endl;
	int i;
	cin >> i;
	return 0;
}
*/

int _tmain(int argc, _TCHAR* argv[])
{
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;



	readStateFile(filePath);
	//Strategy():
	writeMoveFile(filePath);
	return 0;
}

void readStateFile(string filePath)
{
	cout << "Reading state file " << filePath + "/" + "state.json" << std::endl;
	string fileContent;
	string line;
	ifstream myfile(filePath + "/" + "state.json");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fileContent += line += "\n";
		}
		myfile.close();
	}
}

void writeMoveFile(string filePath)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");

	if (outfile.is_open())
	{
		outfile << '5' << std::endl;
		outfile.close();
	}
}
