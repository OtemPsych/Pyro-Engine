#ifndef ButtonNode_H_
#define ButtonNode_H_

#include "SpriteNode.h"
#include "TextNode.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace pyro
{
	class ButtonNode : public SceneNode
	{
	private:
		// Private Member(s)
		SpriteNode* mSprite;
		TextNode*   mText;

	public:
		// Constructor(s)
		ButtonNode();
		// Public Method(s)
		bool handleEvent(const sf::Event& event, sf::RenderWindow& window);

		void setSprite(const sf::Texture& texture);
		void setSprite(const sf::Texture& texture, sf::IntRect rect);

		void setText(const std::string& str, const sf::Font& font);
		void setString(const std::string& str);
	};
}
#endif