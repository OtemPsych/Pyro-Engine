#ifndef Text_H_
#define Text_H_

#include <SFML/Graphics/Text.hpp>

namespace pyro
{
	class Text : public sf::Text
	{
	private:
		sf::Text mOutline;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		Text();
	public:
		void fadeIn(sf::Uint8 rate);
		void fadeOut(sf::Uint8 rate);

		void centerOrigin();

		void setString(const std::string& str);
		void setFont(const sf::Font& font);
		void setCharacterSize(unsigned size);
		void setColor(const sf::Color& color);
		void setStyle(sf::Uint32 style);
	};
}
#endif