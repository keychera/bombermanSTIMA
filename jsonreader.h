#pragma once
#ifndef JSONREADER
#define JSONREADER

#include "json.hpp"

#define jason(j,player,i,...) (j)["RegisteredPlayerEntities"][(i)][#__VA_ARGS__]


#endif

