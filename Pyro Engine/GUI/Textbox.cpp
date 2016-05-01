#include "Textbox.h"

namespace pyro
{
	namespace gui
	{
		Textbox::Textbox(sf::RenderWindow& window, sf::Vector2f size)
			: ClickableGUIEntity(window, size)
			, mActive(false)
			, mCaret(sf::Vector2f(2.f, static_cast<float>(mText.getCharacterSize())))
		{
			sf::FloatRect caretLBounds(mCaret.getLocalBounds());
			mCaret.setOrigin(caretLBounds.width / 2.f, caretLBounds.height / 2.f);
			mCaret.setFillColor(mShape.getFillColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
		}

		void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			ClickableGUIEntity::draw(target, states);

			if (mActive)
				target.draw(mCaret, states.transform *= getTransform());
		}

		void Textbox::handleEvent(const sf::Event& event)
		{
			if (mActive && event.type == sf::Event::TextEntered)
			{
				std::string textString(mText.getString());
				sf::FloatRect textGBounds(mText.getGlobalBounds());

				if (event.text.unicode >= 32 && event.text.unicode <= 127 && textGBounds.width < getGlobalBounds().width / 1.2f)
					mText.setString(textString + static_cast<char>(event.text.unicode));
				else if (event.text.unicode == 8 && !textString.empty())
				{
					textString.pop_back();
					mText.setString(textString);
				}

				mCaret.setPosition(mText.getGlobalBounds().width / 2.f + 5.f, mCaret.getPosition().y);
			}
			else
				mActive = clicked(event, mActive);
		}
	}
}