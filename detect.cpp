#include "stdafx.h"
using namespace std;
using json = nlohmann::json;

Detect::Detect(string key, json _j)
{
	j = _j;
	int i = 0;
	while (player(j, i, Key) != key)
		i++;
	x = playerX(j,i);
	y = playerY(j,i);
	detectionDone = false;
}

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

string Detect::IsAroundSafe()
{
	string out = "1111";
	//check all direction
	out[0] = IsSafe(x + 1, y) ? '1' : '0';
	out[1] = IsSafe(x - 1, y) ? '1' : '0';
	out[2] = IsSafe(x, y + 1) ? '1' : '0';
	out[3] = IsSafe(x, y - 1) ? '1' : '0';
	return out;
}

void Detect::DetectAround(int n)
{
	const int size = (n*n + ((n - 1)*(n - 1)));
	e = new EntityID[size];
	int idx = 0;
	for (int i = -n; i <= n; i++) {
		for (int k = -n + abs(i); k < n - abs(i); k++) {
			string id = (block(j, x + i, y + k, Entity) != "null") ?
				block(j, x + i, y + k, Entity) : block(j, x + i, y + k, PowerUp);
			e[idx].Set(id,x+i,y+k);
			idx++;
		}
	}
}

