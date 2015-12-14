#ifndef Text_H_
#define Text_H_

#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace pyro
{
	class Text : public sf::Text
	{
	public:
		// Constructor(s)
		Text();
		Text(const std::string& string, const sf::Font& font, unsigned charSize = 30);
		// Public Method(s)
		void update();

		void fadeIn(sf::Uint8 rate);
		void fadeOut(sf::Uint8 rate);

		void centerOrigin(bool state = true);
	};
}
#endif