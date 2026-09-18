#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball
	{
	public:
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

		void ReboundFromPlatform();

		const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
		const sf::Vector2f& GetDirection() const { return direction; }

	private:
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f direction = { 0.f,0.f };
		// иниц. вектора направления
	};
}