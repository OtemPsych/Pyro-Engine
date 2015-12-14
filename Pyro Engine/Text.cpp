#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	// Constructor(s)
		// Default
	Text::Text()
	{
		centerOrigin();
	}
		// Constructor 1
	Text::Text(const std::string& string, const sf::Font& font, unsigned charSize)
		: sf::Text(string, font, charSize)
	{
		centerOrigin();
	}

	// Public Method(s)
		// Fade In
	void Text::fadeIn(sf::Uint8 rate)
	{
		sf::Uint8 limit = 255;

		const sf::Color& color = getColor();
		if (color.a < limit)
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a + rate > limit ? limit : color.a + rate));
	}
		// Fade Out
	void Text::fadeOut(sf::Uint8 rate)
	{
		sf::Uint8 limit = 0;

		const sf::Color& color = getColor();
		if (color.a > limit)
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a - rate < limit ? limit : color.a - rate));
	}
		// Center Origin
	void Text::centerOrigin(bool state)
	{
		if (state) {
			sf::FloatRect bounds = getLocalBounds();
			setOrigin(bounds.left + bounds.width / 2.f,
					  bounds.top + bounds.height / 2.f);
		}
		else
			setOrigin(0.f, 0.f);
	}
}