#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace pyro
{
	Text::Text()
		: mShadow(nullptr)
		, mFont(nullptr)
		, mOriginFlags(utils::OriginFlags::Left | utils::OriginFlags::Top)
	{
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (mShadow) 
			target.draw(*mShadow, states);
		target.draw(mText, states);
	}

	void Text::setString(const std::string& string)
	{
		mText.setString(string);
		if (mShadow)
			mShadow->setString(string);

		setOriginFlags(mOriginFlags);
	}

	void Text::setFont(const sf::Font& font)
	{
		mText.setFont(font);
		if (mShadow)
			mShadow->setFont(font);

		mFont.reset();
	}

	void Text::loadFontFromFile(const std::string& filename)
	{
		mFont = std::make_unique<sf::Font>();
		if (!mFont->loadFromFile(filename)) {
			std::cout << "pyro::Text::loadFontFromFile - Failed to load " << filename << std::endl;
			return;
		}

		mText.setFont(*mFont);
		if (mShadow)
			mShadow->setFont(*mFont);
	}

	void Text::setCharacterSize(unsigned size)
	{
		mText.setCharacterSize(size);
		if (mShadow)
			mShadow->setCharacterSize(size);
	}

	void Text::setStyle(sf::Uint32 style)
	{
		mText.setStyle(style);
		if (mShadow)
			mShadow->setStyle(style);
	}

	void Text::setTextColor(const sf::Color& color)
	{
		mText.setColor(color);
	}

	void Text::setOriginFlags(sf::Uint32 originFlags)
	{
		mOriginFlags = originFlags;

		utils::setOriginFlags(mText, originFlags);
		if (mShadow)
			utils::setOriginFlags(*mShadow, originFlags);
	}

	void Text::activateShadow(bool flag)
	{
		if (flag) {
			mShadow = std::make_unique<sf::Text>();
			*mShadow = mText;
		}
		else
			mShadow.reset();
	}

	void Text::setShadowOffset(float xOffset, float yOffset)
	{
		if (mShadow)
			mShadow->setPosition(xOffset, yOffset);
	}

	void Text::setShadowOffset(const sf::Vector2f& offset)
	{
		setShadowOffset(offset.x, offset.y);
	}

	void Text::setShadowColor(const sf::Color& color)
	{
		if (mShadow)
			mShadow->setColor(color);
	}

	sf::FloatRect Text::getGlobalBounds() const
	{
		return getTransform().transformRect(mText.getGlobalBounds());
	}

	const sf::Font* Text::getFont() const
	{
		if (mFont)
			return mFont.get();
		else {
			const sf::Font* textFont(mText.getFont());
			return textFont ? textFont : nullptr;
		}
	}
}