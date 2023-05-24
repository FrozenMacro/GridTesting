#pragma once

#include "raylib.h"
class BarricadeObj
{
public:
	//void Update(float deltaTime);
	void OnHit();
	void Draw();
	void Initialize();
	void setPosition(Vector2 pos);
private:
	Texture texture;
	Rectangle frameRec;
	Vector2 position;
	int blockType; // 0 - 4
	int hit;
	int previousHit;
};

