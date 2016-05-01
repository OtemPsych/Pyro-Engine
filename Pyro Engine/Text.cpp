#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace pyro
{
	Text::Text()
	{
		mOutline.setPosition(1.5f, 1.5f);
		mOutline.setColor(sf::Color::Black);

		centerOrigin();
	}

	void Text::centerOrigin()
	{
		sf::FloatRect textLBounds(mText.getLocalBounds());
		mText.setOrigin(textLBounds.left + textLBounds.width / 2.f,
			            textLBounds.top + textLBounds.height / 2.f);

		sf::FloatRect outlineLBounds(mOutline.getLocalBounds());
		mOutline.setOrigin(outlineLBounds.left + outlineLBounds.width / 2.f,
			               outlineLBounds.top + outlineLBounds.height / 2.f);
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(mOutline, states);
		target.draw(mText, states);
	}

	void Text::setString(const std::string& string)
	{
		mText.setString(string);
		mOutline.setString(string);

		centerOrigin();
	}

	void Text::setFont(const sf::Font& font)
	{
		mText.setFont(font);
		mOutline.setFont(font);
	}

	void Text::setCharacterSize(unsigned size)
	{
		mText.setCharacterSize(size);
		mOutline.setCharacterSize(size);
	}

	void Text::setStyle(sf::Uint32 style)
	{
		mText.setStyle(style);
		mOutline.setStyle(style);
	}

	void Text::setColor(const sf::Color& color)
	{
		mText.setColor(color);
		mOutline.setColor(color == sf::Color::Black ? sf::Color::White : sf::Color::Black);
	}

	sf::FloatRect Text::getGlobalBounds() const
	{
		return getTransform().transformRect(mText.getGlobalBounds());
	}
}