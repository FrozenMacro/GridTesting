#include "PlayerSprite.h"
#include "raylib.h"

void PlayerSprite::Initialize() {
	texture = LoadTexture("Resources/spaceship.png");
	frameRec = { 0, 0, 13, 6 };
}

float PlayerSprite::lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

void PlayerSprite::setForce(float nF){
	force = nF;
}

void PlayerSprite::setPosition(Vector2 pos) {
	position = pos;
}

Vector2 PlayerSprite::getPosition() {
	return position;
}

void PlayerSprite::Update(float deltaTime) {
	if (IsKeyDown(KEY_LEFT))
	{
		position.x -= force * deltaTime;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		position.x += force * deltaTime;
	}
}

void PlayerSprite::Draw(){
	DrawTextureRec(texture, frameRec, { position.x - (frameRec.width / 2), position.y - 4}, RAYWHITE);
	DrawCircle(position.x, position.y, 2, RAYWHITE);
}
