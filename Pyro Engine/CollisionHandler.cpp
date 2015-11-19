#include "CollisionHandler.h"

#include <SFML/Graphics/Texture.hpp>

namespace pyro
{
	// Private Method(s)
		// Check Bounding Box Collision
	bool CollisionHandler::checkBoundingBoxCollision(const SpriteNode& e1, const SpriteNode& e2) const
	{
		if (e1.mSprite.getGlobalBounds().intersects(e2.mSprite.getGlobalBounds()))
			return true;
		else
			return false;
	}
		// Check Pixel Collision
	bool CollisionHandler::checkPixelCollision(const SpriteNode& e1, const SpriteNode& e2) const
	{
		sf::Image image1 = e1.mSprite.getTexture()->copyToImage(),
				  image2 = e2.mSprite.getTexture()->copyToImage();

		sf::IntRect bounds1 = static_cast<sf::IntRect>(e1.mSprite.getGlobalBounds()),
				    bounds2 = static_cast<sf::IntRect>(e2.mSprite.getGlobalBounds());

		sf::IntRect boxBounds(std::max(bounds1.left, bounds2.left),
							  std::max(bounds1.top, bounds2.top),
							  std::min(bounds1.width, bounds2.width),
							  std::min(bounds1.height, bounds2.height));

		for (int i = boxBounds.left; i < boxBounds.width; i++)
			for (int j = boxBounds.top; j < boxBounds.height; j++)
			{
				sf::Color color1 = image1.getPixel(i - bounds1.left, j - bounds1.top),
						  color2 = image2.getPixel(i - bounds2.left, j - bounds2.top);

				if (color1.a > 0 && color2.a > 0)
					return true;
			}

		return false;
	}

	// Public Method(s)
		// Check Collision | Single, Single
	bool CollisionHandler::checkCollision(const SpriteNode& e1, const SpriteNode& e2,
										  bool pixelCollision) const
	{
		if (checkBoundingBoxCollision(e1, e2))
			if (pixelCollision) {
				if (checkPixelCollision(e1, e2))
					return true;
			}
			else
				return true;

		return false;
	}
		// Check Collision | Single, Multiple
	const CollisionHandler::SprPair CollisionHandler::checkCollision(const SpriteNode& e1, const SprVector& e2,
																	 bool pixelCollision) const
	{
		for (const auto& i : e2)
			if (checkCollision(e1, i, pixelCollision))
				return SprPair(&i, nullptr);

		return SprPair(nullptr, nullptr);
	}
		// Check Collision | Multiple, Multiple
	const CollisionHandler::SprPair CollisionHandler::checkCollision(const SprVector& e1, const SprVector& e2,
																	 bool pixelCollision) const
	{
		for (const auto& i : e1)
			for (const auto& j : e2)
				if (checkCollision(i, j, pixelCollision))
					return SprPair(&i, &j);

		return SprPair(nullptr, nullptr);
	}
}