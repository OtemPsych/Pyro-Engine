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
			sf::RectangleShape mShape;
			Text               mText;

		private:
			void centerOrigin();
		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:
			ClickableGUIEntity(sf::RenderWindow& window, sf::Vector2f size);
			virtual ~ClickableGUIEntity();
		public:
			bool hover();
			bool clicked(const sf::Event& event, bool previousFlag = false);

			sf::FloatRect getGlobalBounds() const;

			inline sf::RectangleShape& getShape() { return mShape; }
			inline Text& getText() { return mText; }
		};
	}
}
#endif