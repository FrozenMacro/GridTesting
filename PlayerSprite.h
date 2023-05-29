#pragma once
#include "raylib.h"

class PlayerSprite
{
public:
	void Initialize();
	void setForce(float newForce);
	void setPosition(Vector2 pos);
	Vector2 getPosition();
	void Update(float deltaTime);
	void Draw();
	float lerp(float a, float b, float t);
private:
	Texture texture;
	Vector2 position;
	Rectangle frameRec;
	float force = 150;
};

