#pragma once

#include "raylib.h"
#include "TileObject.h"
#include "Barricade.h"
#include "Bullet.h"
#include "PlayerSprite.h"
#include <vector>
class GameManager
{
public:

	GameManager();
	~GameManager();

	void Start();
	void DestroyBullet(int index);

	Vector2 startPos = {200, 275};
	PlayerSprite player;

	std::vector<Barricade> barricades;
	std::vector<Bullet> bullets;
private:
	void Update(float deltaTime);
	void Draw();

	void Initialize();
	void Destroy();
	float lerp(float a, float b, float t);
private:
	int gameWidth = 400, gameHeight = 300;
};