#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	Text::Text()
	{
		centerOrigin();
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mOutline, this->getTransform());
		target.draw(*this);
	}

	void Text::fadeIn(sf::Uint8 rate)
	{
		sf::Uint8 limit = 255;

		const sf::Color& color = getColor();
		if (color.a < limit)
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a + rate > limit ? limit : color.a + rate));
	}

	void Text::fadeOut(sf::Uint8 rate)
	{
		sf::Uint8 limit = 0;

		const sf::Color& color = getColor();
		if (color.a > limit)
			setColor(sf::Color(color.r, color.g, color.b,
							   color.a - rate < limit ? limit : color.a - rate));
	}

	void Text::centerOrigin()
	{
		sf::FloatRect bounds = getLocalBounds();
		setOrigin(bounds.left + bounds.width / 2.f,
				  bounds.top + bounds.height / 2.f);
	}

	void Text::generalUpdate()
	{
		mOutline.setFont(*(this->getFont()));
		mOutline.setString(this->getString());

		mOutline.setCharacterSize(this->getCharacterSize());
		mOutline.setScale(this->getScale());
		mOutline.setRotation(this->getRotation());
		mOutline.setStyle(this->getStyle());

		mOutline.setOrigin(this->getOrigin());
		mOutline.setPosition(2.f, 2.f);

		sf::Color color(this->getColor());
		mOutline.setColor(sf::Color(255 - color.r, 255 - color.g, 255 - color.b));
	}

	void Text::updateString()
	{
		mOutline.setString(this->getString());
	}
}