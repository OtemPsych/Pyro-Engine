#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	Text::Text()
	{
		centerOrigin();

		mOutline.setPosition(2.f, 2.f);
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mOutline, this->getTransform());
		target.draw(static_cast<sf::Text>(*this));
	}

	void Text::fadeIn(sf::Uint8 rate)
	{
		sf::Uint8 limit = 255;

		const sf::Color& color = getColor();
		if (color.a < limit)
		{
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a + rate > limit ? limit : color.a + rate));

			const sf::Color& outlineColor = mOutline.getColor();
			mOutline.setColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b,
										outlineColor.a + rate > limit ? limit : outlineColor.a + rate));
		}
	}

	void Text::fadeOut(sf::Uint8 rate)
	{
		sf::Uint8 limit = 0;

		const sf::Color& color = getColor();
		if (color.a > limit)
		{
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a - rate < limit ? limit : color.a - rate));

			const sf::Color& outlineColor = mOutline.getColor();
			mOutline.setColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b,
				outlineColor.a - rate < limit ? limit : outlineColor.a - rate));
		}
	}

	void Text::setString(const std::string& str)
	{
		sf::Text::setString(str);
		mOutline.setString(str);
	}

	void Text::setFont(const sf::Font& font)
	{
		sf::Text::setFont(font);
		mOutline.setFont(font);
	}

	void Text::setCharacterSize(unsigned size)
	{
		sf::Text::setCharacterSize(size);
		mOutline.setCharacterSize(size);
	}

	void Text::setColor(const sf::Color& color)
	{
		sf::Text::setColor(color);
		mOutline.setColor(sf::Color(255 - color.r, 255 - color.g, 255 - color.b));
	}

	void Text::setStyle(sf::Uint32 style)
	{
		sf::Text::setStyle(style);
		mOutline.setStyle(style);
	}

	void Text::centerOrigin()
	{
		sf::FloatRect bounds = getLocalBounds();
		setOrigin(bounds.left + bounds.width / 2.f,
				  bounds.top + bounds.height / 2.f);

		sf::FloatRect outlineBounds = mOutline.getLocalBounds();
		mOutline.setOrigin(outlineBounds.left + outlineBounds.width / 2.f,
						   outlineBounds.top + outlineBounds.height / 2.f);
	}
}