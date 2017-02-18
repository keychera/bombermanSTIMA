#include "stdafx.h"
using namespace std;
using json = nlohmann::json;

Detect::~Detect()
{
	if (detectionDone)
		delete e;
}

bool Detect::IsSafe()
{
	
	int xSize = mapX(j);
	int ySize = mapY(j);

	bool safe = true;
	bool trulySafe = false;
	
	//to the right
	int i = x, k = y;
	while ((safe) && (!trulySafe) && (i <= xSize)) {
		trulySafe = ((block(j, i, k, Entity) == IndestructibleWall) || (block(j, i, k, Entity) == DestructibleWall));
		if (!trulySafe) {
			if (haveBomb(j, i, k)) {
				int radius = bRadius(j, i, k);
				safe = (radius < abs(i - x));
			}
		}
		i++;
	}
	if (safe) {

		//to the left
		bool trulySafe = false;
		int i = x, k = y;
		while ((safe) && (!trulySafe) && (i <= xSize)) {
			trulySafe = ((block(j, i, k, Entity) == IndestructibleWall) || (block(j, i, k, Entity) == DestructibleWall));
			if (!trulySafe) {
				if (haveBomb(j, i, k)) {
					int radius = bRadius(j, i, k);
					safe = (radius < abs(i - x));
				}
			}
			i--;

		}
		if (safe) {

			//upward
			bool trulySafe = false;
			int i = x, k = y;
			while ((safe) && (!trulySafe) && (i <= xSize)) {
				trulySafe = ((block(j, i, k, Entity) == IndestructibleWall) || (block(j, i, k, Entity) == DestructibleWall));
				if (!trulySafe) {
					if (haveBomb(j, i, k)) {
						int radius = bRadius(j, i, k);
						safe = (radius < abs(k - y));
					}
				}
			}
			k++;

			if (safe) {

				//downward
				bool trulySafe = false;
				int i = x, k = y;
				while ((safe) && (!trulySafe) && (i <= xSize)) {
					trulySafe = ((block(j, i, k, Entity) == IndestructibleWall) || (block(j, i, k, Entity) == DestructibleWall));
					if (!trulySafe) {
						if (haveBomb(j, i, k)) {
							int radius = bRadius(j, i, k);
							safe = (radius < abs(k - y));
						}
					}
					k--;

				}
			}
		}
	}

	return safe;

}

bool Detect::IsSafe(int _x, int _y)
{
	int xSize = mapX(j);
	int ySize = mapY(j);

	bool safe = true;
	bool trulySafe = false;
	
	//to the right
	int i = _x, k = _y;
	while ((safe) && (!trulySafe) && (i <= xSize)) {
		trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
		if (!trulySafe) {
			if (haveBomb(j, i, k)) {
				int radius = bRadius(j, i, k);
				safe = (radius < abs(i - _x));
			}
		}
		i++;
	}
	if (safe) {

		//to the left
		bool trulySafe = false;
		int i = _x, k = _y;
		while ((safe) && (!trulySafe) && (i <= xSize)) {
			trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
			if (!trulySafe) {
				if (haveBomb(j, i, k)) {
					int radius = bRadius(j, i, k);
					safe = (radius < abs(i - _x));
				}
			}
			i--;

		}
		if (safe) {

			//upward
			bool trulySafe = false;
			int i = _x, k = _y;
			while ((safe) && (!trulySafe) && (i <= xSize)) {
				trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
				if (!trulySafe) {
					if (haveBomb(j, i, k)) {
						int radius = bRadius(j, i, k);
						safe = (radius < abs(k - _y));
					}
				}
			}
			k++;

			if (safe) {

				//downward
				bool trulySafe = false;
				int i = _x, k = _y;
				while ((safe) && (!trulySafe) && (i <= xSize)) {
					trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
					if (!trulySafe) {
						if (haveBomb(j, i, k)) {
							int radius = bRadius(j, i, k);
							safe = (radius < abs(k - _y));
						}
					}
					k--;

				}
			}
		}
	}
	return safe;
}

bool Detect::IsEntity(int _x, int _y)
{
	return (block(j, _x, _y, Entity) != "null");
}

string Detect::IsAroundSafe()
{
	string out = "0000";
	out[0] = IsSafe(x, y + 1) ? 1 : 0;
	out[1] = IsSafe(x - 1, y) ? 1 : 0;
	out[2] = IsSafe(x + 1, y) ? 1 : 0;
	out[3] = IsSafe(x, y - 1) ? 1 : 0;
	return out;
}

void Detect::DetectAround(int n)
{
	detectionDone = true;
	const int size = (n*n + ((n - 1)*(n - 1)));
	detectionArea = size;
	e = new EntityID[size];
	int idx = 0;
	for (int i = -n; i <= n; i++) {
		for (int k = -n + abs(i); k < n - abs(i); k++) {
			string id = (block(j, x + i, y + k, Entity) != "null") ?
				block(j, i, k, Entity) : block(j, i, k, PowerUp);
			e[idx].Set(id,x+i,y+k);
			idx++;
		}
	}
}


bool Detect::IsDestructibleAdjacent()
{
	bool yes;
	int i = 0, k = 0;
	for (int i = -1; i <= 1; i++) {
		for (int k = (-1 + abs(i)); k < (1 - abs(i)); k++) {
			yes = (block(j, x + i, y + k, Entity) == DestructibleWall);
		}
	}
	return yes;
}

bool Detect::IsEscapePossible()
{
	bool yes = false;
	int i = -1,k = -1;

	//check diagonal block
	while ((!yes) && (abs(i) < (bag * 3) + 1)){
		k = -1;
		yes |= ((block(j, x + i, y, Entity) == "null") && (block(j, x + i, y + k, Entity) == "null"));
		yes |= ((block(j, x + i, y, Entity) == "null") && (block(j, x + i, y + abs(k), Entity) == "null"));
		yes |= ((block(j, x + abs(i), y, Entity) == "null") && (block(j, x + abs(i), y + k, Entity) == "null"));
		yes |= ((block(j, x + abs(i), y, Entity) == "null") && (block(j, x + abs(i), y + abs(k), Entity) == "null"));
		i--;
	}

	i = -1, k = -1;
	while ((!yes) && (abs(k) < bag)) {
		i = -1;
		yes |= ((block(j, x, y + k, Entity) == "null") && (block(j, x + i, y + k, Entity) == "null"));
		yes |= ((block(j, x, y + k, Entity) == "null") && (block(j, x + abs(i), y + k, Entity) == "null"));
		yes |= ((block(j, x, y + abs(k), Entity) == "null") && (block(j, x + i, y + abs(k), Entity) == "null"));
		yes |= ((block(j, x, y + abs(k), Entity) == "null") && (block(j, x + abs(i), y + abs(k), Entity) == "null"));
		k--;
	}
	return yes;
}

EntityID Detect::IsSuperPowerUpAround()
{
	int i = 0;
	bool found = false;
	while ((!found) && (i < detectionArea)) {
		found = (e[i].GetID() == SuperPowerup);
		i++;
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
			if (DistanceFromHere(e[i]) < minDist) {
				minDist = DistanceFromHere(e[i]);
				chosen = i;
			}
		}
	}
	EntityID eOut;
	if (chosen != -1) eOut = e[chosen];
	return eOut;
}

EntityID Detect::IsDestructibleAround()
{
	int i,chosen = -1;
	double minDist = 9999.0f;
	for (i = 0; i < detectionArea;i++) {
		if (e[i].GetID() == DestructibleWall) {
			if (DistanceFromHere(e[i]) < minDist) {
				minDist = DistanceFromHere(e[i]);
				chosen = i;
			}
		}
	}
	EntityID eOut;
	if (chosen != -1) eOut = e[chosen];
	return eOut;
}

double Detect::DistanceFromHere(EntityID e)
{
	return sqrt((e.GetX() - x)*(e.GetX() - x) + (e.GetY() - y)*(e.GetY() - y));
}



int Detect::GetX() { return x; }
int Detect::GetY() { return y; }

