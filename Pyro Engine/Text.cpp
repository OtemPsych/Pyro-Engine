#include "Text.h"
#include "Utils.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace pyro
{
	Text::Text()
		: mOriginFlags(utils::OriginFlags::Left | utils::OriginFlags::Top)
	{
	}

	void Text::recalculateOriginFlags()
	{
		utils::setOriginFlags(mText, mOriginFlags);
		utils::setOriginFlags(mShadow, mOriginFlags);
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(mShadow, states);
		target.draw(mText, states);
	}

	void Text::setString(const std::string& string)
	{
		mText.setString(string);
		mShadow.setString(string);

		recalculateOriginFlags();
	}

	void Text::setFont(const sf::Font& font)
	{
		mText.setFont(font);
		mShadow.setFont(font);

		recalculateOriginFlags();
	}

	void Text::setCharacterSize(unsigned size)
	{
		mText.setCharacterSize(size);
		mShadow.setCharacterSize(size);

		recalculateOriginFlags();
	}

	void Text::setStyle(sf::Uint32 style)
	{
		mText.setStyle(style);
		mShadow.setStyle(style);

		recalculateOriginFlags();
	}

	void Text::setTextColor(const sf::Color& color)
	{
		mText.setColor(color);
	}

	void Text::setOriginFlags(sf::Uint16 originFlags)
	{
		mOriginFlags = originFlags;
		recalculateOriginFlags();
	}

	void Text::setShadowOffset(float xOffset, float yOffset)
	{
		mShadow.setPosition(xOffset, yOffset);
		recalculateOriginFlags();
	}

	void Text::setShadowOffset(const sf::Vector2f& offset)
	{
		setShadowOffset(offset.x, offset.y);
	}

	void Text::setShadowColor(const sf::Color& color)
	{
		mShadow.setColor(color);
	}

	sf::FloatRect Text::getGlobalBounds() const
	{
		return getTransform().transformRect(mText.getGlobalBounds());
	}
}