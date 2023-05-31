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

float clamp(float v, float min, float max)
{
	float v1 = v;
	if (v1 < min) { v1 = min; }
	if (v1 > max) { v1 = max; }
	return v1;
}

void PlayerSprite::OnHit(int livesLeft) {
	hit = true;
	frameRec.x += frameRec.width;
	timer = 3;
}

void PlayerSprite::Update(float deltaTime) {
	if (hit) {
		if (timer > 0) {
			timer -= deltaTime;
		}
		else if(timer <= 0){
			timer = 0;
			hit = false;
			position.x = 150;
			Initialize();
		}
	}
	else
	{
		if (IsKeyDown(KEY_LEFT))
		{
			position.x -= force * deltaTime;
		}

		if (IsKeyDown(KEY_RIGHT))
		{
			position.x += force * deltaTime;
		}
	}

	position.x = clamp(position.x, 0 + frameRec.width / 2, 275 - frameRec.width / 2);
}

void PlayerSprite::Draw(){
	min = { position.x - frameRec.width / 2, position.y - frameRec.height / 2};
	max = { position.x + frameRec.width / 2, position.y + frameRec.height / 2};
	DrawTextureRec(texture, frameRec, { position.x - (frameRec.width / 2), position.y - 4}, RAYWHITE);
	//DrawCircle(position.x, position.y, 2, RAYWHITE);
}
