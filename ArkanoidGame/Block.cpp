#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	void Block::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		SetupSprite(sprite, BLOCK_WIDTH, BLOCK_HEIGHT, texture);
		SetSpriteColor(sprite, sf::Color(150, 200, 255));

		isDestroyed = false;
	}

	void Block::Update(float timeDelta)
	{
		
	}

	void Block::Draw(sf::RenderWindow& window)
	{
		if (!isDestroyed)
		{
			GameObject::Draw(window);
		}
	}

	void Block::SetPosition(float x, float y)
	{
		sprite.setPosition(x, y);
	}

	void Block::Destroy()
	{
		isDestroyed = true;
	}
}