#include <SFML/Graphics/Rect.hpp>

namespace pyro
{
	namespace utils
	{
		template <typename T>
		Resource<T>::Resource(T amount)
			: original(amount)
			, current(amount)
		{
		}

		template <class T>
		void setOriginFlags(T& t, sf::Uint32 originFlags)
		{
			const sf::FloatRect lBounds(t.getLocalBounds());
			if (originFlags == OriginFlags::Center) {
				t.setOrigin(lBounds.left + lBounds.width / 2.f, lBounds.top + lBounds.height / 2.f);
				return;
			}

			sf::Vector2f newOrigin;
			if (originFlags & OriginFlags::CenterX)
				newOrigin.x = lBounds.left + lBounds.width / 2.f;
			else if (originFlags & OriginFlags::Left)
				newOrigin.x = 0.f;
			else if (originFlags & OriginFlags::Right)
				newOrigin.x = lBounds.left + lBounds.width;

			if (originFlags & OriginFlags::CenterY)
				newOrigin.y = lBounds.top + lBounds.height / 2.f;
			else if (originFlags & OriginFlags::Top)
				newOrigin.y = 0.f;
			else if (originFlags & OriginFlags::Bottom)
				newOrigin.y = lBounds.top + lBounds.height;

			t.setOrigin(newOrigin);
		}
	}
}