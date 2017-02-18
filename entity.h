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
	@brief constructor
	*/
	EntityID(std::string n, int _x, int _y);

	/*!
	@brief copy constructor
	*/
	EntityID(const EntityID&);

	/*!
	@brief operator= overload
	*/
	EntityID& operator=(const EntityID&);

	/*!
	@brief entity setter
	*/
	void Set(std::string n, int _x, int _y);

	std::string GetID();

	int GetX();

	int GetY();

private:
	std::string id;
	int x;
	int y;
};

#endif // !