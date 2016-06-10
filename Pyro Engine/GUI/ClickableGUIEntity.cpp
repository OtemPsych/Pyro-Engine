#include "ClickableGUIEntity.h"
#include "../Utils.h"

namespace pyro
{
	namespace gui
	{
		ClickableGUIEntity::ClickableGUIEntity(sf::RenderWindow& window, sf::Vector2f size)
			: mWindow(window)
			, mBox(size)
			, mOriginFlags(utils::OriginFlags::Left | utils::OriginFlags::Top)
		{
		}

		ClickableGUIEntity::~ClickableGUIEntity()
		{
		}

		void ClickableGUIEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(mBox, states.transform *= getTransform());
			target.draw(mText, states);
		}

		bool ClickableGUIEntity::hover()
		{
			return getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
		}

		bool ClickableGUIEntity::clicked(const sf::Event& event, bool previousFlag)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				return hover();
			else
				return previousFlag;
		}

		void ClickableGUIEntity::setOriginFlags(sf::Uint16 originFlags)
		{
			mOriginFlags = originFlags;

			utils::setOriginFlags(*this, originFlags);
			mText.setOriginFlags(mText.getOriginFlags());
		}

		sf::FloatRect ClickableGUIEntity::getLocalBounds() const
		{
			return mBox.getLocalBounds();
		}

		sf::FloatRect ClickableGUIEntity::getGlobalBounds() const
		{
			return getTransform().transformRect(mBox.getGlobalBounds());
		}
	}
}