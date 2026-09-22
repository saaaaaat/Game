#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <cassert>
#include <cmath>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		// платформа и шарик
		gameObjects.emplace_back(std::make_shared<Platform>());
		gameObjects.emplace_back(std::make_shared<Ball>());

		// блок
		const int rows = 5;
		const int columns = 10;
		const float startX = 60.f;
		const float startY = 60.f;
		const float spacingX = 72.f;
		const float spacingY = 30.f;

		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				auto block = std::make_shared<Block>();
				block->Init();
				block->SetPosition(
					startX + col * spacingX,
					startY + row * spacingY
				);
				blocks.push_back(block);
			}
		}

		// ин. объектов
		for (auto& object : gameObjects)
		{
			object->Init();
		}

		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		// обновление для обьектов
		for (auto& object : gameObjects)
		{
			object->Update(timeDelta);
		}

		// обновление блоков
		for (auto& block : blocks)
		{
			block->Update(timeDelta);
		}

		const Platform* platform = (Platform*)gameObjects[0].get();
		Ball* ball = (Ball*)gameObjects[1].get();

		// столкновение  платформой
		bool hit = platform->CheckCollisionWithBall(*ball);
		if (hit && ball->GetDirection().y > 0)
		{
			ball->ReboundFromPlatform();
		}

		// столкновение с блоком
		for (auto& block : blocks)
		{
			if (block->IsDestroyed())
			{
				continue;
			}

			if (ball->GetRect().intersects(block->GetRect()))
			{
				sf::Vector2f ballPos = ball->GetPosition();
				sf::Vector2f blockPos = block->GetPosition();

				float dx = ballPos.x - blockPos.x;
				float dy = ballPos.y - blockPos.y;

				if (std::fabs(dx) > std::fabs(dy))
				{
					ball->ReboundHorizontally();
				}
				else
				{
					ball->ReboundVertically();
				}

				block->Destroy();

				break;
			}
		}

		// проверка на уничтожение
		bool allBlocksDestroyed = true;
		for (auto& block : blocks)
		{
			if (!block->IsDestroyed())
			{
				allBlocksDestroyed = false;
				break;
			}
		}

		if (allBlocksDestroyed)
		{
			Application::Instance().GetGame().PushState(GameStateType::Win, false);
			return;   
		}

		// проигрыш
		bool gameOver = !hit && ball->GetPosition().y > platform->GetRect().top;

		if (gameOver)
		{
			gameOverSound.play();
			Application::Instance().GetGame().PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(background);

		
		for (auto& object : gameObjects)
		{
			object->Draw(window);
		}

		//блоки
		for (auto& block : blocks)
		{
			block->Draw(window);
		}

		scoreText.setOrigin(CalculateTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);
	}
}