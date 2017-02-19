#include "stdafx.h"

EntityID::EntityID()
{
	id = "null";
	x = 0;
	y = 0;
	BombRadius = -1;
}

EntityID::EntityID(std::string n, int _x, int _y)
{
	id = n;
	x = _x;
	y = _y;
	BombRadius = -1;
}

EntityID::EntityID(std::string n, int _x, int _y, int r)
{
	id = n;
	x = _x;
	y = _y;
	BombRadius = r;
}

EntityID::EntityID(const EntityID &e)
{
	id = e.id;
	x = e.x;
	y = e.y;
	BombRadius = e.BombRadius;
}

EntityID & EntityID::operator=(const EntityID &e)
{
	id = e.id;
	x = e.x;
	y = e.y;
	BombRadius = e.BombRadius;
	return *this;
}

void EntityID::Set(std::string n, int _x, int _y)
{
	id = n;
	x = _x;
	y = _y;
	BombRadius = -1;
}

void EntityID::Set(std::string n, int _x, int _y,int r)
{
	id = n;
	x = _x;
	y = _y;
	BombRadius = r;
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

int EntityID::GetRadius() {
	return BombRadius;
}
