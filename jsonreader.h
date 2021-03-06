#pragma once
#ifndef JSONREADER
#define JSONREADER

#include "json.hpp"

#define Round(j) (j)["CurrentRound"].get<int>()

/*	TIPE ENTITY
	IndestructibleWall - Wall yang tidak bisa dihancurkan '#'
	DestructibleWall - Wall yang bisa hancur '+'
	PlayerEntity - Entity merupakan player
*/
#define IndestructibleWall "Domain.Entities.IndestructibleWallEntity, Domain"
#define DestructibleWall "Domain.Entities.DestructibleWallEntity, Domain"
#define PlayerEntity "Domain.Entities.PlayerEntity, Domain"
#define Bomb "Bomb"

/*	TIPE POWERUP
	SuperPowerup - Simbol '$'
	BagPowerup	- Simbol '&'
	RadiusPowerup - Simbol '!'
*/
#define SuperPowerup "Domain.Entities.PowerUps.SuperPowerUp, Domain"
#define BagPowerup "Domain.Entities.PowerUps.BombBagPowerUpEntity, Domain"
#define RadiusPowerup "Domain.Entities.PowerUps.BombRaduisPowerUpEntity, Domain"

/*	AVAILABLE PLAYER COMMAND
	j: variable json
	i: indeks player
	...:
	Name		- Nama player
	Key			- Player key
	Points		- Jumlah point player
	Killed		- Player Alive or Dead
	BombBag		- Jumlah bomb yang bisa dilepas player
	BombRadius	- Radius bomb per cell
	Location  //Use playerX & playerY instead of this
*/
#define player(j,i,...) (j)["RegisteredPlayerEntities"][(i)][#__VA_ARGS__]
#define playerX(j,i) (j)["RegisteredPlayerEntities"][(i)]["Location"]["X"].get<int>()
#define playerY(j,i) (j)["RegisteredPlayerEntities"][(i)]["Location"]["Y"].get<int>()

/*	MAP SIZE
	j: variable json

	mapX - Lebar Map(Horizontal)
	mapY - Tinggi Map(Vertical)
*/
#define mapX(j) (j)["MapWidth"].get<int>()
#define mapY(j) (j)["MapHeight"].get<int>()

/*	BOMB CHECKER
	haveBomb(j,i,k) - untuk mengecek apakah block tertentu ada bomb
	bRadius(j,i,k)	- Radius bomb pada block, return -1 jika tidak ada bomb
	bTimer(j,i,k)	- Timer bomb pada block, return -1 jika tidak ada bomb
	j: variable json
	i: koordinat X
	k: koordinat Y
*/
#define haveBomb(j,i,k)	((j)["GameBlocks"][(i-1)][(k-1)]["Bomb"].is_null() ? false : true)
#define bRadius(j,i,k) (haveBomb(j,i,k) ? (j)["GameBlocks"][(i-1)][(k-1)]["Bomb"]["BombRadius"].get<int>() : -1)
#define bTimer(j,i,k) (haveBomb(j,i,k) ? (j)["GameBlocks"][(i-1)][(k-1)]["Bomb"]["BombTimer"].get<int>() : -1)

/*	GAME BLOCK
	j : variable json
	i : koordinat X
	k : koordinat Y
	...:
	Entity	- Tipe entity pada block (lihat daftar tipe), jika tidak ada entity nilainya "null"
	PowerUp	- Tipe powerup pada block, jika tidak ada power up nilainya "null"
*/
#define block(j,i,k,...) (!(j)["GameBlocks"][(i-1)][(k-1)][#__VA_ARGS__].is_null() ? (j)["GameBlocks"][(i-1)][(k-1)][#__VA_ARGS__]["$type"].get<std::string>() : "null")

#endif

