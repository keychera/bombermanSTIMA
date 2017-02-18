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
	Detect(std::string key, nlohmann::json _j);

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

	/*!
	@brief this will check if tiles around the player is a safe place to move
	@return string of 4 character to mark which direction is safe
	string format
		1st char = right
		2nd char = left
		3rd char = up
		4th char = down
	example 1011 -> right is the only direction that is not safe
	it will marked 1 if there is no possible move in one direction
	*/
	std::string IsAroundSafe();

	/*!
	@brief this will detect what is around the player location x,y
	this will modify detectionList d
	*/
	void DetectAround(int n);

	bool IsDestructibleOneTileAway();

	int IsEscapePossible();

	EntityID IsSuperPowerUpAround();

	EntityID IsPowerUpAround();

	EntityID IsDestructibleAround();

	int GetX();

	int GetY();

private:
	bool detectionDone;
	int x;
	int y;
	nlohmann::json j;
	EntityID *e;
};

#endif