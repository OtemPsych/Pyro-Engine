#include "TextNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	// Constructor(s)
		// Default
	TextNode::TextNode()
		: mText()
	{
		centerOrigin();
	}
		// Constructor 1
	TextNode::TextNode(const std::string& string, const sf::Font& font)
		: mText(string, font)
	{
		centerOrigin();
	}

	// Private Method(s)
		// Draw Current
	void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mText, states);
	}

	// Public Method(s)
		// Fade In
	void TextNode::fadeIn(sf::Uint8 rate)
	{
		sf::Uint8 limit = 255;

		const auto& color = mText.getColor();
		if (color.a < limit)
			mText.setColor(sf::Color(color.r, color.g, color.b,
									 color.a + rate > limit ? limit : color.a + rate));
	}
		// Fade Out
	void TextNode::fadeOut(sf::Uint8 rate)
	{
		sf::Uint8 limit = 0;

		const auto& color = mText.getColor();
		if (color.a > limit)
			mText.setColor(sf::Color(color.r, color.g, color.b,
									 color.a - rate < limit ? limit : color.a - rate));
	}
		// Center Origin
	void TextNode::centerOrigin()
	{
		auto bounds = mText.getLocalBounds();
		mText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}
}