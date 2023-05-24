#include "BarricadeObj.h"
#include "raylib.h"
#include <iostream>

void BarricadeObj::Initialize()
{
	texture = LoadTexture("Resources/blockSheet.png");
	frameRec = { 0, 0, 6, 6 };
}

void BarricadeObj::setPosition(Vector2 pos) {
	position = { pos.x - 4, pos.y - 4 };
}

void BarricadeObj::OnHit() {
	hit++;
}

void BarricadeObj::Draw()
{
	float casted1 = (float)hit, casted2 = (float)blockType;
	if (previousHit != hit)
	{
		std::cout << "NEW HIT, CHANGING FRAME" << std::endl;
		frameRec = { casted1, casted2, 6, 6 };
		DrawTextureRec(texture, frameRec, position, RAYWHITE);
	}

	previousHit = hit;
}