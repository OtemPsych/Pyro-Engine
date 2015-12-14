#include "Button.h"

namespace pyro
{
	// Private Method(s)
		// Draw
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

	// Public Method(s)
		// Handle Event
	bool Button::handleEvent(const sf::Event& event, sf::RenderWindow& window)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			
			sf::FloatRect spriteBounds(mSprite.getGlobalBounds());

			sf::Vector2f spriteOrigin(mSprite.getOrigin());
			sf::Vector2f currPos(getPosition());
			currPos.x -= spriteOrigin.x;
			currPos.y -= spriteOrigin.y;

			sf::FloatRect bounds(currPos.x, currPos.y, spriteBounds.width, spriteBounds.height);
			if (mousePos.x >= bounds.left && mousePos.x <= bounds.left + bounds.width
				&& mousePos.y >= bounds.top && mousePos.y <= bounds.top + bounds.height)
				return true;
		}

		return false;
	}
		// Center Origin
	void Button::centerOrigin()
	{
		sf::FloatRect sprBounds(mSprite.getLocalBounds());
		mSprite.setOrigin(sprBounds.width / 2.f, sprBounds.height / 2.f);
	}
}