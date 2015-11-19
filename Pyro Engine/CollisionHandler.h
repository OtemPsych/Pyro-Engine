#ifndef CollisionHandler_H_
#define CollisionHandler_H_

#include "SpriteNode.h"

namespace pyro
{
	class CollisionHandler : private sf::NonCopyable
	{
	private:
		// Private Typedef(s)
		using SprPair = std::pair<const SpriteNode*, const SpriteNode*>;
		using SprVector = std::vector<SpriteNode>;

	private:
		// Private Method(s)
		bool checkBoundingBoxCollision(const SpriteNode& e1, const SpriteNode& e2) const;
		bool checkPixelCollision(const SpriteNode& e1, const SpriteNode& e2) const;
	public:
		// Public Method(s)
		bool		  checkCollision(const SpriteNode& e1, const SpriteNode& e2,
									 bool pixelCollision = false) const;

		const SprPair checkCollision(const SpriteNode& e1, const SprVector& e2,
									 bool pixelCollision = false) const;

		const SprPair checkCollision(const SprVector& e1, const SprVector& e2,
									 bool pixelCollision = false) const;
	};
}
#endif