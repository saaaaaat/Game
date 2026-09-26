#pragma once
#include "Block.h"

namespace ArkanoidGame
{
	class DurableBlock : public Block
	{
	public:
		DurableBlock(const sf::Vector2f& position);

		void OnHit() override;
		void Update(float timeDelta) override;

	private:
		int hitPoints = 3;
	};
}