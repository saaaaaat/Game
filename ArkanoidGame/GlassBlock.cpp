#include "GlassBlock.h"

namespace ArkanoidGame
{
	GlassBlock::GlassBlock(const sf::Vector2f& position)
		: Block(position, sf::Color(255, 255, 255, 100))   // прозрачный 
	{
	}

	void GlassBlock::OnHit()
	{
		hitCount = 0;   // ломается сразу
	}
}