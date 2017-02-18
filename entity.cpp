#include "stdafx.h"

EntityID::EntityID()
{
	id = "null";
	x = 0;
	y = 0;
}

EntityID::EntityID(std::string n, int _x, int _y)
{
	id = n;
	x = _x;
	y = _y;
}

EntityID::EntityID(const EntityID &e)
{
	id = e.id;
	x = e.x;
	y = e.y;
}

EntityID & EntityID::operator=(const EntityID &e)
{
	id = e.id;
	x = e.x;
	y = e.y;
	return *this;
}

void EntityID::Set(std::string n, int _x, int _y)
{
	id = n;
	x = _x;
	y = _y;
}

std::string EntityID::GetID()
{
	return id;
}

int EntityID::GetX()
{
	return x;
}

int EntityID::GetY()
{
	return y;
}
