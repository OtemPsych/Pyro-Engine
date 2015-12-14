#ifndef CollisionHandler_H_
#define CollisionHandler_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace pyro
{
	class CollisionHandler : private sf::NonCopyable
	{
	private:
		// Private Typedef(s)
		using SprVector = std::vector<sf::Sprite>;
	public:
		// Public Struct(s)
		struct CollisionVec 
		{
			const sf::Sprite* spr1;
			const sf::Sprite* spr2;
			bool			  condition;

			CollisionVec(const sf::Sprite* pSpr1 = nullptr, const sf::Sprite* pSpr2 = nullptr,
						 bool pCondition = false);
		};
	private:
		// Private Method(s)
		bool checkBoundingBoxCollision(const sf::Sprite& e1, const sf::Sprite& e2) const;
		bool checkPixelCollision(const sf::Sprite& e1, const sf::Sprite& e2) const;
	public:
		// Public Method(s)
		bool		 checkCollision(const sf::Sprite& e1, const sf::Sprite& e2,
									bool pixelCollision = false) const;

		CollisionVec checkCollision(const sf::Sprite& e1, const SprVector& e2,
									bool pixelCollision = false) const;

		CollisionVec checkCollision(const SprVector& e1, const SprVector& e2,
									bool pixelCollision = false) const;
	};
}
#endif