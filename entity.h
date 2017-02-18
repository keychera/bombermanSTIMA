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
	EntityID(std::string n, int x, int y);

	/*!
	@brief entity setter
	*/
	void Set(std::string n, int x, int y);

private:
	std::string id;
	int x;
	int y;
};

#endif // !