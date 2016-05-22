#ifndef Text_H_
#define Text_H_

#include "Utils.h"

#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace pyro
{
	class Text : public sf::Transformable, public sf::Drawable
	{
	private:
		sf::Text                  mText;
		std::unique_ptr<sf::Text> mShadow;
		std::unique_ptr<sf::Font> mFont;
		sf::Uint32                mOriginFlags;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Text();
	public:
		void setString(const std::string& string);
		void setFont(const sf::Font& font);
		void loadFontFromFile(const std::string& filename);
		void setCharacterSize(unsigned size);
		void setStyle(sf::Uint32 style);
		void setTextColor(const sf::Color& color);
		void setOriginFlags(sf::Uint32 originFlags);

		void activateShadow(bool flag);
		void setShadowOffset(float xOffset, float yOffset);
		void setShadowOffset(const sf::Vector2f& offset);
		void setShadowColor(const sf::Color& color);

		sf::FloatRect getGlobalBounds() const;

		const sf::Font*            getFont() const;
		inline const sf::String&   getString() const { return mText.getString(); }
		inline unsigned            getCharacterSize() const { return mText.getCharacterSize(); }
		inline sf::Uint32          getStyle() const { return mText.getStyle(); }
		inline const sf::Color&    getTextColor() const { return mText.getColor(); }
		inline sf::Uint32          getOriginFlags() const { return mOriginFlags; }
		inline bool                isShadowActive() const { return mShadow != nullptr; }
		inline const sf::Vector2f* getShadowOffset() const { return mShadow ? &mShadow->getPosition() : nullptr; }
		inline const sf::Color*    getShadowColor() const { return mShadow ? &mShadow->getColor() : nullptr; }
	};
}
#endif