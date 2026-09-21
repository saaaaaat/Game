#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball;

	class Platform :public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		

		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }
		bool CheckCollisionWithBall(const Ball& ball) const;

	private:
		void Move(float step);

		
	};
}