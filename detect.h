#pragma once

#include "jsonreader.h"
#include "entity.h"

class Detect {
public:
	/*!
	@brief constructor
	@param x,y player location to check
	*/
	Detect(int x, int y);

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
	bool IsSafe(int x, int y);

	/*!
	@brief this will check if tiles around the player is a safe place to move
	@return string of 4 character to mark which direction is safe
	string format
		1st char = up
		2nd char = right
		3rd char = down
		4th char = left
	example 1011 -> right is the only direction that is not safe
	it will marked 1 if there is no possible move in one direction
	*/
	string IsAroundSafe();

	/*!
	@brief this will detect what is around the player location x,y
	this will modify detectionList d
	*/
	void DetectAround(int n);



private:
	bool detectionDone;
	int x;
	int y;
	json j;
	Entity *e;
};