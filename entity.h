#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class EntityID {
public:
	/*!
	@brief default constructor
	*/
	EntityID();
	/*!
	@brief constructor without radius
	*/
	EntityID(std::string n, int _x, int _y );
	/*!
	@brief constructor with radius
	*/
	EntityID(std::string n, int _x, int _y,int r);
	

	/*!
	@brief copy constructor
	*/
	EntityID(const EntityID&);

	/*!
	@brief operator= overload
	*/
	EntityID& operator=(const EntityID&);

	/*!
	@brief entity setter without radius
	*/
	void Set(std::string n, int _x, int _y);

	/*!
	@brief entity setter with radius
	*/
	void Set(std::string n, int _x, int _y,int r);

	std::string GetID();

	int GetX();

	int GetY();

	int GetRadius();

private:
	std::string id;
	int x;
	int y;
	int BombRadius;
};

#endif // !