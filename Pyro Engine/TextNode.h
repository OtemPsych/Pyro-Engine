#ifndef TextNode_H_
#define TextNode_H_

#include "SceneNode.h"

#include <SFML/Graphics/Text.hpp>

namespace pyro
{
	class TextNode : public SceneNode
	{
	private:
		// Private Member(s)
		sf::Text mText;

	private:
		// Private Method(s)
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		// Constructor(s)
		TextNode();
		TextNode(const std::string& string, const sf::Font& font);
		// Public Method(s)
		void fadeIn(sf::Uint8 rate);
		void fadeOut(sf::Uint8 rate);

		void setString(const std::string& str);

		virtual void centerOrigin();

		inline sf::Text& getText() { return mText; }
	};
}
#endif