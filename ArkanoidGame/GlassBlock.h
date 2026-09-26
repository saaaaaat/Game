#pragma once
#include "Block.h"

namespace ArkanoidGame
{
	class GlassBlock : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& position);

		void OnHit() override;
		bool IsTransparent() const override { return true; }
	};
}