#ifndef ClickableGUIEntity_H_
#define ClickableGUIEntity_H_

#include "../Text.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace pyro
{
	namespace gui
	{
		class ClickableGUIEntity : public sf::Transformable, public sf::Drawable
		{
		private:
			sf::RenderWindow&  mWindow;
		protected:
			sf::RectangleShape mBox;
			Text               mText;
			sf::Uint16         mOriginFlags;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		public:
			ClickableGUIEntity(sf::RenderWindow& window, sf::Vector2f size);
			virtual ~ClickableGUIEntity();
		public:
			bool hover();
			bool clicked(const sf::Event& event, bool previousFlag = false);

			void setOriginFlags(sf::Uint16 originFlags);

			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;

			inline sf::RectangleShape&       getBox() { return mBox; }
			inline const sf::RectangleShape& getBox() const { return mBox; }
			inline Text&                     getText() { return mText; }
		};
	}
}
#endif