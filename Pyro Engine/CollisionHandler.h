#ifndef CollisionHandler_H_
#define CollisionHandler_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace pyro
{
	class CollisionHandler : private sf::NonCopyable
	{
	private:
		// Private Method(s)
		bool checkBoundingBoxCollision(const sf::Sprite& e1, const sf::Sprite& e2) const;
		bool checkPixelCollision(const sf::Sprite& e1, const sf::Sprite& e2) const;
	public:
		// Public Method(s)
		bool checkCollision(const sf::Sprite& e1, const sf::Sprite& e2,
							bool pixelCollision = false) const;
	};
}
#endif