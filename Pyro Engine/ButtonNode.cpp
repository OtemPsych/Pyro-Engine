#include "ButtonNode.h"

namespace pyro
{
	// Constructor(s)
		// Default
	ButtonNode::ButtonNode()
		: mSprite(nullptr)
		, mText(nullptr)
	{
	}

	// Public Method(s)
		// Handle Event
	bool ButtonNode::handleEvent(const sf::Event& event, sf::RenderWindow& window)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			auto bounds = mSprite->getWorldBounds();

			if (mousePos.x >= bounds.left && mousePos.x <= bounds.left + bounds.width
				&& mousePos.y >= bounds.top && mousePos.y <= bounds.top + bounds.height)
				return true;
		}

		return false;
	}
		// Set Sprite
	void ButtonNode::setSprite(const sf::Texture& texture)
	{
		sf::Vector2u textureSize(texture.getSize());
		setSprite(texture, sf::IntRect(0, 0, textureSize.x, textureSize.y));
	}
		// Set Sprite
	void ButtonNode::setSprite(const sf::Texture& texture, sf::IntRect rect)
	{
		std::unique_ptr<SpriteNode> sprite(new SpriteNode(texture, rect));

		if (mSprite != nullptr)
			detachChild(*mSprite);
		mSprite = sprite.get();
		attachChild(std::move(sprite));

		mSprite->centerOrigin();
	}
		// Set Text
	void ButtonNode::setText(const std::string& str, const sf::Font& font)
	{
		std::unique_ptr<TextNode> text(new TextNode(str, font));

		if (mText != nullptr)
			detachChild(*mText);
		mText = text.get();
		attachChild(std::move(text));
	}
		// Set String
	void ButtonNode::setString(const std::string& str)
	{
		mText->setString(str);
	}
}