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
	Detect(std::string key, nlohmann::json _j,int n);

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
		1st char = up
		2nd char = left
		3rd char = right
		4th char = down
	example 1011 -> up, right, down are the possible move that is also safe
	it will marked 0 if there is no possible move in one direction(marked safe)
	*/
	std::string IsAroundSafe();

	/*!
	@brief this will check if tiles around the the input location x,y is a safe place to move
	@return string of 4 character to mark which direction is safe
	string format
	1st char = up
	2nd char = left
	3rd char = right
	4th char = down
	example 1011 -> up, right, down are the possible move that is also safe
	it will marked 0 if there is no possible move in one direction(marked safe)
	*/
	std::string IsAroundSafe(int _x, int _y);

	/*!
	@brief this will tell id there is any destructible adjacent to the player
	@return true or false
	*/
	bool IsDestructibleAdjacent();

	/*!
	@brief this will search SuperPowerUp in the detection area
	@return an Entity containing the location of the SuperPowerUp if found,
	an EntityID with id "null" if not
	*/
	EntityID IsSuperPowerUpAround();

	/*!
	@brief this will search the closest PowerUp (RadiusPowerUp or BombBagPowerUp) in the detection area
	@return an Entity containing the location of the PowerUp if found,
	an EntityID with id "null" if not
	*/
	EntityID IsPowerUpAround();
	
	/*!
	@brief this will search the closest Destructible Wall in the detection area
	@return an Entity containing the location of the Destructible Wall if found,
	an EntityID with id "null" if not
	*/
	EntityID IsDestructibleAround();

	/*!
	@brief this will calculate the distance from player location to input EntityID
	@return the double value of the distance
	*/
	double DistanceFromHere(EntityID in);

	/*!
	@brief getter of x value, which represent the x location of the center of detection area
	*/
	int GetX();

	/*!
	@brief getter of y value, which represent the y location of the center of detection area
	*/
	int GetY();


private:
	int detectionArea;
	int detectionRadius;
	int x;
	int y;
	int radius;
	int bag;
	nlohmann::json j;
	EntityID *e;
};

#endif