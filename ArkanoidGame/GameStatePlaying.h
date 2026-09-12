#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;
		sf::SoundBuffer gameOverSoundBuffer;

		Platform platform;
		Ball ball;

		sf::Text scoreText;
		
		sf::RectangleShape background;

		sf::Sound gameOverSound;
	};
}