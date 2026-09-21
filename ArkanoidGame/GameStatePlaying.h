#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include <vector>
#include <memory>

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		sf::Font font;
		sf::SoundBuffer gameOverSoundBuffer;

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;

		sf::Text scoreText;
		sf::RectangleShape background;

		sf::Sound gameOverSound;
	};
}