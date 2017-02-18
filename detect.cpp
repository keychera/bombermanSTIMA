#include "stdafx.h"
using namespace std;
using json = nlohmann::json;

Detect::~Detect()
{
	if (detectionDone)
		delete [] e;
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
		trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
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
			trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
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
				trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
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
					trulySafe = (block(j, i, k, Entity) == IndestructibleWall);
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

bool Detect::IsAroundSafe()
{
	bool out =
		IsSafe(x + 1, y) &&
		IsSafe(x - 1, y) &&
		IsSafe(x, y + 1) &&
		IsSafe(x, y - 1);
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

bool Detect::IsDestructibleOneTileAway()
{
	bool yes = false;
	for (int i = -1; i <= 1; i++) {
		for (int k = -1 + abs(i); k < 1 - abs(i); k++) {
			yes |= (block(j, x + i, y + k, Entity) == DestructibleWall);
		}
	}
	return yes;
}

bool Detect::IsEscapePossible()
{
	bool yes = false;
	int i = -1,k = -1;
	//check diagonal block

	while ((!yes) && (abs(i) < bag)){
		k = -1;
		yes |= ((block(j, x + i, 0, Entity) != "null") && (block(j, x + i, k, Entity) != "null"));
		yes |= ((block(j, x + i, 0, Entity) != "null") && (block(j, x + i, abs(k), Entity) != "null"));
		yes |= ((block(j, x + abs(i), 0, Entity) != "null") && (block(j, x + abs(i), k, Entity) != "null"));
		yes |= ((block(j, x + abs(i), 0, Entity) != "null") && (block(j, x + abs(i), abs(k), Entity) != "null"));
		i--;
	}

	while ((!yes) && (abs(k) < bag)) {
		i = -1;
		yes |= ((block(j, x + k, 0, Entity) != "null") && (block(j, x + k, i, Entity) != "null"));
		yes |= ((block(j, x + k, 0, Entity) != "null") && (block(j, x + k, abs(i), Entity) != "null"));
		yes |= ((block(j, x + abs(k), 0, Entity) != "null") && (block(j, x + abs(k), i, Entity) != "null"));
		yes |= ((block(j, x + abs(k), 0, Entity) != "null") && (block(j, x + abs(k), abs(i), Entity) != "null"));
		k--;
	}
	return yes;
}

EntityID Detect::IsSuperPowerUpAround()
{
	int i = 0;
	bool found = false;
	while ((!found) && (i < detectionArea)) {
		found = (e[i].GetID == SuperPowerup);
		i++;
	}
	EntityID eOut;
	if (found) eOut = e[i];
	return eOut;
}



int Detect::GetX() { return x; }
int Detect::GetY() { return y; }

