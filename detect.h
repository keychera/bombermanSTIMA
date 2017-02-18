#pragma once
#ifndef DETECT_H
#define DETECT_H


#include "jsonreader.h"
#include "entity.h"
#include <string>
/*

*/
class Detect {
public:
	/*!
	@brief constructor
	@param x,y player location to check
	*/
	Detect(std::string key, nlohmann::json _j) {
		j = _j;
		int i = 0;
		while (player(j, i, Key).get<std::string>() != key)
			i++;
		x = playerX(j, i);
		y = playerY(j, i);
		radius = player(j, i, BombRadius).get<int>();
		bag = player(j, i, BombBag).get<int>();
		detectionDone = false;
		detectionArea = 0;
	}

	/*!
	@brief destructor
	*/
	~Detect();

	/*!
	@brief this will check if player location x,y is safe from bombs reach
	@return true or false
	*/
	bool IsSafe();
	
	/*!
	@brief this will check if input location x,y is safe from bombs reach
	@return true or false
	*/
	bool IsSafe(int _x, int _y);

	bool IsEntity(int _x, int _y);

	/*!
	@brief this will check if tiles around the player is a safe place to move
	@return string of 4 character to mark which direction is safe
	string format
		1st char = up
		2nd char = left
		3rd char = right
		4th char = down
	example 1011 -> left is the only direction that is not safe
	it will marked 0 if there is no possible move in one direction
	*/
	std::string IsAroundSafe();

	/*!
	@brief this will detect what is around the player location x,y
	this will modify detectionList d
	*/
	void DetectAround(int n);

	/*!
	@brief this will tell id there is any destructible adjacent to the player
	@return true or false
	*/
	bool IsDestructibleAdjacent();

	/*!
	@brief this will tell if there is any escape if the player put the bomb
	@return true or false
	if false, it will erase destructible in the entity list
	*/
	bool IsEscapePossible();

	EntityID IsSuperPowerUpAround();

	EntityID IsPowerUpAround();

	EntityID IsDestructibleAround();

	double DistanceFromHere(EntityID in);

	int GetX();

	int GetY();


private:
	bool detectionDone;
	int detectionArea;
	int x;
	int y;
	int radius;
	int bag;
	nlohmann::json j;
	EntityID *e;
};

#endif