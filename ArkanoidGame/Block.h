#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		void SetPosition(float x, float y);
		void Destroy();
		bool IsDestroyed() const { return isDestroyed; }

	private:
		bool isDestroyed = false;
	};
}