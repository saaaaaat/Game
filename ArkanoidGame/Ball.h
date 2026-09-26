#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public Colladiable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();
		void ChangeAngle(float angle);

		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;

	private:
		void OnHit() override;

		sf::Vector2f direction;
		float lastAngle = 90.f;
	};
}