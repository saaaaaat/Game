#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	void Platform::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));
		SetupSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.0f });
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-timeDelta * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * PLATFORM_SPEED);
		}
	}

	void Platform::Draw(sf::RenderWindow& window)
	{
		RenderSprite(sprite, window);
	}

	void Platform::Move(float step)
	{
		sf::Vector2f position = sprite.getPosition();
		position.x += step;

		float leftLimit = PLATFORM_WIDTH / 2.f;
		float rightLimit = SCREEN_WIDTH - PLATFORM_WIDTH / 2.f;

		if (position.x < leftLimit) position.x = leftLimit;
		if (position.x > rightLimit) position.x = rightLimit;

		sprite.setPosition(position);
	}

	bool Platform::CheckCollisionWithBall(const Ball& ball)
	{
		sf::FloatRect rect = sprite.getGlobalBounds();
		sf::Vector2f ballPos = ball.GetPosition();
		float halfBall = BALL_SIZE / 2.f;

		// шарик слева
		if (ballPos.x < rect.left)
		{
			float dx = ballPos.x - rect.left;
			float dy = ballPos.y - rect.top;
			return (dx * dx + dy * dy) < halfBall * halfBall;
		}

		// шарик справа
		if (ballPos.x > rect.left + rect.width)
		{
			float dx = ballPos.x - (rect.left + rect.width);
			float dy = ballPos.y - rect.top;
			return (dx * dx + dy * dy) < halfBall * halfBall;
		}

		// шарик над
		return std::fabs(ballPos.y - rect.top) <= halfBall;
	}
}