#pragma once
#include "raylib.h"
#include "TileObject.h"
#include <vector>

class Barricade
{
public:
	/*Barricade();
	~Barricade();*/
	void Intialize();
	void Draw();
	void setPosition(Vector2 pos);
	std::vector<TileObject> objects;
	Vector2 position;
private:
};

