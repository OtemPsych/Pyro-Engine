#ifndef Button_H_
#define Button_H_

#include "Text.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace pyro
{
	class Button : public sf::Transformable, public sf::Drawable
	{
	public:
		// Public Member(s)
		sf::Sprite mSprite;
		Text	   mText;

	private:
		// Private Method(s)
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		// Public Method(s)
		bool handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void centerOrigin();
	};
}
#endif