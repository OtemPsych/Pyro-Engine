#ifndef Text_H_
#define Text_H_

#include <SFML/Graphics/Text.hpp>

namespace pyro
{
	class Text : public sf::Text
	{
	public:
		// Constructor(s)
		Text();
		// Public Method(s)
		void fadeIn(sf::Uint8 rate);
		void fadeOut(sf::Uint8 rate);

		void centerOrigin();
	};
}
#endif