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
	int blockType; // 0 - 4
private:
	Texture texture;
	Rectangle frameRec;
	Vector2 position;
	int hit = 0;
};

