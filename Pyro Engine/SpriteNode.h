#ifndef SpriteNode_H_
#define SpriteNode_H_

#include "SceneNode.h"

#include <SFML/Graphics/Sprite.hpp>

namespace pyro
{
	class SpriteNode : public SceneNode
	{
		friend class CollisionHandler;
	protected:
		// Protected Member(s)
		sf::Sprite mSprite;

	private:
		// Private Method(s)
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		// Constructor(s)
				 SpriteNode();
		explicit SpriteNode(const sf::Texture& texture);
				 SpriteNode(const sf::Texture& texture, sf::IntRect rect);
		// Public Method(s)
		virtual void centerOrigin();

		sf::FloatRect getWorldBounds();
	};
}
#endif