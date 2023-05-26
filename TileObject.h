#pragma once

#include "raylib.h"
class TileObject
{
public:
	//void Update(float deltaTime);
	void OnHit();
	void Draw();
	void Initialize();
	void setPosition(Vector2 pos);
	bool Overlapping(Vector2 min, Vector2 max);
	Vector2 min, max;
	int blockType; // 0 - 4
private:
	Texture texture;
	Rectangle frameRec;
	Vector2 position;
	int hit = 0;
};

