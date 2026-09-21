#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;

		void ReboundFromPlatform();
		void ReboundVertically() { direction.y *= -1; }
		void ReboundHorizontally() { direction.x *= -1; }

		const sf::Vector2f& GetDirection() const { return direction; }

	private:
		sf::Vector2f direction = { 0.f, 0.f };
	};
}