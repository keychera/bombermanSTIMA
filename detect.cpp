#include "stdafx.h"
using namespace std;
using json = nlohmann::json;

Detect::Detect(std::string key, nlohmann::json _j,int n) {
	j = _j;
	int i = 0;
	while (player(j, i, Key).get<std::string>() != key)
		i++;
	x = playerX(j, i);
	y = playerY(j, i);
	radius = player(j, i, BombRadius).get<int>();
	bag = player(j, i, BombBag).get<int>();
	//int n = mapX(j) / 2;
	int size = (n*n + ((n + 1)*(n + 1)));
	detectionArea = size;
	e = new EntityID[size];
	int idx = 0;
	for (i = -n; i <= n; i++) {
		for (int k = -n + abs(i); k <= n - abs(i); k++) {
			if (((x + i) > 1) && ((x + i) < mapX(j)) && ((y + k) > 1) && ((y + k) < mapY(j))) {
				if (haveBomb(j,x+i,y+k)) {
					string id = Bomb;
					int radius = bRadius(j, x+i, y+k);
					e[idx].Set(id, x + i, y + k,radius);
				}
				else {
					string id = (block(j, x + i, y + k, Entity) != "null") ?
						block(j, x+i, y+k, Entity) : block(j, x+i, y+k, PowerUp);
					e[idx].Set(id, x + i, y + k);
				}
				idx++;
			}
		}
	}
	detectionRadius = n;
}

Detect::~Detect()
{
	delete [] e;
}

bool Detect::IsSafe()
{
	bool safe;

	if (!haveBomb(j, x, y)) {
		safe = true;
		int i = 0;
		bool RightSafe = false, LeftSafe = false, UpSafe = false, DownSafe = false;
		while (i < detectionArea) {
			if ((e[i].GetID() == IndestructibleWall) || (e[i].GetID() == DestructibleWall)) {
				RightSafe |= ((e[i].GetX() - x) - 1 == 0 && e[i].GetY() == y);
				LeftSafe |= ((e[i].GetX() - x) + 1 == 0 && e[i].GetY() == y);
				UpSafe |= ((e[i].GetY() - y) + 1 == 0 && e[i].GetX() == x);
				DownSafe |= ((e[i].GetY() - y) - 1 == 0 && e[i].GetX() == x);
			}
			i++;
		}
		bool VerticalSafe = UpSafe && DownSafe, HorizontalSafe = RightSafe && LeftSafe;
		i = 0;
		while ((safe) && (i < detectionArea)) {
			if (e[i].GetID() == Bomb) {
				if (!VerticalSafe)
					if (e[i].GetX() == x) {
						safe = !(abs(e[i].GetY() - y) <= e[i].GetRadius());
					}
				if (safe)
					if (!HorizontalSafe)
						if (e[i].GetY() == y) {
							safe = !(abs(e[i].GetX() - x) <= e[i].GetRadius());
						}
			}
			if (safe) i++;
		}
	}
	else {
		safe = false;
	}
	return safe;

}

bool Detect::IsSafe(int _x, int _y)
{
	bool safe = true;

	if (!haveBomb(j, _x, _y)) {
		safe = true;
		int i = 0;
		bool RightSafe = false, LeftSafe = false, UpSafe = false, DownSafe = false;
		while (i < detectionArea) {
			if ((e[i].GetID() == IndestructibleWall) || (e[i].GetID() == DestructibleWall)) {
				RightSafe |= ((e[i].GetX() - _x) - 1 == 0 && e[i].GetY() == _y);
				LeftSafe |= ((e[i].GetX() - _x) + 1 == 0 && e[i].GetY() == _y);
				UpSafe |= ((e[i].GetY() - _y) + 1 == 0 && e[i].GetX() == _x);
				DownSafe |= ((e[i].GetY() - _y) - 1 == 0 && e[i].GetX() == _x);
			}
			i++;
		}
		bool VerticalSafe = UpSafe && DownSafe, HorizontalSafe = RightSafe && LeftSafe;
		i = 0;
		while ((safe) && (i < detectionArea)) {
			if (e[i].GetID() == Bomb) {
				if (!VerticalSafe)
					if (e[i].GetX() == _x) {
						safe = !(abs(e[i].GetY() - _y) <= e[i].GetRadius());
					}
				if (safe)
					if (!HorizontalSafe)
						if (e[i].GetY() == _y) {
							safe = !(abs(e[i].GetX() - _x) <= e[i].GetRadius());
						}
			}
			if (safe) i++;
		}
	}
	else {
		safe = false;
	}

	return safe;
}

string Detect::IsAroundSafe()
{
	string out = "0000";
	out[0] = (IsSafe(x, y - 1) && (block(j, x, y - 1, Entity) == "null")) ? '1' : '0';
	out[1] = (IsSafe(x - 1, y) && (block(j, x - 1, y, Entity) == "null")) ? '1' : '0';
	out[2] = (IsSafe(x + 1, y) && (block(j, x + 1, y, Entity) == "null")) ? '1' : '0';
	out[3] = (IsSafe(x, y + 1) && (block(j, x, y + 1, Entity) == "null")) ? '1' : '0';
	return out;
}

string Detect::IsAroundSafe(int _x,int _y)
{
	string out = "0000";
	out[0] = (IsSafe(_x, _y - 1)&& (block(j, _x, _y - 1, Entity) == "null")) ? '1' : '0';
	out[1] = (IsSafe(_x - 1, _y)&& (block(j, _x - 1, _y, Entity) == "null")) ? '1' : '0';
	out[2] = (IsSafe(_x + 1, _y) && (block(j, _x + 1, _y, Entity) == "null")) ? '1' : '0';
	out[3] = (IsSafe(_x, _y + 1) && (block(j, _x, _y + 1, Entity) == "null")) ? '1' : '0';
	return out;
}

bool Detect::IsDestructibleAdjacent()
{
	bool yes = false;
	int i = 0;
	while((!yes)&&(i < detectionArea)) {
		if (e[i].GetID() == DestructibleWall) {
			yes = (DistanceFromHere(e[i]) == 1.0);
		}
		if (!yes) i++;
	}
	return yes;
}

EntityID Detect::IsSuperPowerUpAround()
{
	int i = 0;
	bool found = false;
	while ((!found) && (i < detectionArea)) {
		found = (e[i].GetID() == SuperPowerup);
		if(!found) i++;
	}
	EntityID eOut;
	if (found) eOut = e[i];
	return eOut;
}

EntityID Detect::IsPowerUpAround()
{
	int i,chosen = -1;
	double minDist = 9999.0f;
	for (i = 0; i < detectionArea;i++) {
		if ((e[i].GetID() == BagPowerup) || (e[i].GetID() == RadiusPowerup)) {
			if (DistanceFromHere(e[i]) <= minDist) {
				minDist = DistanceFromHere(e[i]);
				chosen = i;
			}
		}
	}
	EntityID eOut;
	if (chosen != -1)
		return e[chosen];
	else
		return eOut;

}

EntityID Detect::IsDestructibleAround()
{
	int i,chosen = -1;
	double minDist = 9999.0f;
	for (i = 0; i < detectionArea;i++) {
		if (e[i].GetID() == DestructibleWall) {
			if (DistanceFromHere(e[i]) <= minDist) {
				minDist = DistanceFromHere(e[i]);
				chosen = i;
			}
		}
	}
	EntityID eOut;
	if (chosen != -1)
		return e[chosen];
	else
		return eOut;
}

double Detect::DistanceFromHere(EntityID e)
{
	return sqrt((e.GetX() - x)*(e.GetX() - x) + (e.GetY() - y)*(e.GetY() - y));
}

int Detect::GetX() { return x; }

int Detect::GetY() { return y; }

