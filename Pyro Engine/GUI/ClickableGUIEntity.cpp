#include "ClickableGUIEntity.h"

namespace pyro
{
	namespace gui
	{
		ClickableGUIEntity::ClickableGUIEntity(sf::RenderWindow& window, sf::Vector2f size)
			: mWindow(window)
			, mShape(size)
		{
			centerOrigin();
		}

		ClickableGUIEntity::~ClickableGUIEntity()
		{
		}

		void ClickableGUIEntity::centerOrigin()
		{
			sf::FloatRect shapeLBounds(mShape.getLocalBounds());
			mShape.setOrigin(shapeLBounds.width / 2.f, shapeLBounds.height / 2.f);
		}

		void ClickableGUIEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();

			target.draw(mShape, states);
			target.draw(mText, states);
		}

		bool ClickableGUIEntity::hover()
		{
			return getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)));
		}

		bool ClickableGUIEntity::clicked(const sf::Event& event, bool previousFlag)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				return getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)));
			else
				return previousFlag;
		}

		sf::FloatRect ClickableGUIEntity::getGlobalBounds() const
		{
			return getTransform().transformRect(mShape.getGlobalBounds());
		}
	}
}