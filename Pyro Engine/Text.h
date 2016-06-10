#ifndef Text_H_
#define Text_H_

#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace pyro
{
	class Text : public sf::Transformable, public sf::Drawable
	{
	private:
		sf::Text   mText;
		sf::Text   mShadow;
		sf::Uint16 mOriginFlags;

	private:
		void recalculateOriginFlags();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Text();
	public:
		void setString(const std::string& string);
		void setFont(const sf::Font& font);
		void setCharacterSize(unsigned size);
		void setStyle(sf::Uint32 style);
		void setTextColor(const sf::Color& color);
		void setOriginFlags(sf::Uint16 originFlags);

		void setShadowOffset(float xOffset, float yOffset);
		void setShadowOffset(const sf::Vector2f& offset);
		void setShadowColor(const sf::Color& color);

		sf::FloatRect getGlobalBounds() const;

		inline const sf::Font*     getFont() const { return mText.getFont(); }
		inline const sf::String&   getString() const { return mText.getString(); }
		inline unsigned            getCharacterSize() const { return mText.getCharacterSize(); }
		inline sf::Uint32          getStyle() const { return mText.getStyle(); }
		inline const sf::Color&    getTextColor() const { return mText.getColor(); }
		inline sf::Uint16          getOriginFlags() const { return mOriginFlags; }
		inline const sf::Vector2f& getShadowOffset() const { return mShadow.getPosition(); }
		inline const sf::Color&    getShadowColor() const { return mShadow.getColor(); }
	};
}
#endif