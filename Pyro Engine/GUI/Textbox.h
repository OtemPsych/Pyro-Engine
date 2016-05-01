#ifndef Textbox_H_
#define Textbox_H_

#include "ClickableGUIEntity.h"

namespace pyro
{
	namespace gui
	{
		class Textbox : public ClickableGUIEntity
		{
		private:
			bool               mActive;
			sf::RectangleShape mCaret;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:
			Textbox(sf::RenderWindow& window, sf::Vector2f size);
		public:
			void handleEvent(const sf::Event& event);
		};
	}
}
#endif