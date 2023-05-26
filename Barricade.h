#pragma once
#include "raylib.h"
#include "TileObject.h"

class Barricade
{
public:
	/*Barricade();
	~Barricade();*/
	void Intialize();
	void Draw();
	void setPosition(Vector2 pos);
	TileObject objects[12];
private:
	Vector2 position;
	Vector2 start_pos;
};

