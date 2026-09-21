#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>
#include <cmath>

namespace
{
	const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		SetupSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.0f });

		float angle = 45.f + rand() % 90;
		float pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		sf::Vector2f pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		// отскок от боковых стен
		if (pos.x - BALL_SIZE / 2.f <= 0 || pos.x + BALL_SIZE / 2.f >= SCREEN_WIDTH)
		{
			direction.x *= -1;
		}

		// отскок от верха и низа
		if (pos.y - BALL_SIZE / 2.f <= 0 || pos.y + BALL_SIZE / 2.f >= SCREEN_HEIGHT)
		{
			direction.y *= -1;
		}
	}

	void Ball::ReboundFromPlatform()
	{
		direction.y *= -1;
	}
}