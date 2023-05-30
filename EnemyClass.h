#pragma once
#include "raylib.h"
class EnemyClass
{
public:
	void Initialize();
	void Update(float deltaTime, bool running);
	void Draw();
	void setPosition(Vector2 pos);
private:
	Vector2 position;
	Texture sprite;
	Rectangle frameRec;
};

