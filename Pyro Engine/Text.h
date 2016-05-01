#ifndef Text_H_
#define Text_H_

#include <SFML/Graphics/Text.hpp>

namespace pyro
{
	class Text : public sf::Transformable, public sf::Drawable
	{
	private:
		sf::Text mText;
		sf::Text mOutline;

	private:
		void centerOrigin();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		Text();
	public:
		void setString(const std::string& string);
		void setFont(const sf::Font& font);
		void setCharacterSize(unsigned size);
		void setStyle(sf::Uint32 style);
		void setColor(const sf::Color& color);

		sf::FloatRect getGlobalBounds() const;

		inline const sf::String& getString() const { return mText.getString(); }
		inline unsigned getCharacterSize() const { return mText.getCharacterSize(); }
	};
}
#endif