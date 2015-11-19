#include "SpriteNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	// Constructor(s)
		// Default
	SpriteNode::SpriteNode()
	{
	}
		// Constructor 1
	SpriteNode::SpriteNode(const sf::Texture& texture)
		: mSprite(texture)
	{
	}
		// Constructor 2
	SpriteNode::SpriteNode(const sf::Texture& texture, sf::IntRect rect)
		: mSprite(texture, rect)
	{
	}

	// Private Method(s)
		// Draw Current
	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
	}

	// Public Method(s)
		// Center Origin
	void SpriteNode::centerOrigin()
	{
		auto bounds = mSprite.getLocalBounds();
		mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}
		// Get World Bounds
	sf::FloatRect SpriteNode::getWorldBounds()
	{
		auto worldPos = getWorldPosition();
		auto bounds = mSprite.getGlobalBounds();
		auto origin = mSprite.getOrigin();

		worldPos.x -= origin.x;
		worldPos.y -= origin.y;
		
		return sf::FloatRect(worldPos.x,
			 				 worldPos.y,
							 bounds.width,
							 bounds.height);
		
	}
}