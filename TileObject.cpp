#include "TileObject.h"
#include "raylib.h"
#include <iostream>

void TileObject::Initialize()
{
	texture = LoadTexture("Resources/blockSheet.png");
	frameRec = { 0, 0, 6, 6 };
}

void TileObject::setPosition(Vector2 pos) {
	position = { pos.x - 4, pos.y - 4 };
}

void TileObject::OnHit() {
	hit++;
}

void TileObject::Draw()
{
	frameRec.x = hit * 6;
	frameRec.y = blockType * 6;
	min = { position.x, position.y }, max = { position.x + frameRec.width, position.y + frameRec.height };
	DrawTextureRec(texture, frameRec, position, RAYWHITE);
}