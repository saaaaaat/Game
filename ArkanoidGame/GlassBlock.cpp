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

	bool GlassBlock::CheckCollision(std::shared_ptr<Colladiable> collidable)
	{
		if (GetCollision(collidable))
		{
			OnHit();   // только блок ломается

			// НЕ вызываем collidable->OnHit() — шарик не меняет угол

			return true;
		}
		return false;
	}
}