#pragma once

class Entity {
public:
	/*!
	@brief default constructor
	*/
	Entity();
	/*!
	@brief constructor
	*/
	Entity(string n, int x, int y);

	/*!
	@brief entity setter
	*/
	Set(string n, int x, int y);

private:
	string type;
	int x;
	int y;
};