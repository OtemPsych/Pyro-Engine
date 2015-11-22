#include "CollisionHandler.h"

#include <SFML/Graphics/Texture.hpp>

namespace pyro
{
	// Private Method(s)
		// Check Bounding Box Collision
	bool CollisionHandler::checkBoundingBoxCollision(const sf::Sprite& e1, const sf::Sprite& e2) const
	{
		if (e1.getGlobalBounds().intersects(e2.getGlobalBounds()))
			return true;
		else
			return false;
	}

	bool CollisionHandler::checkPixelCollision(const sf::Sprite& e1, const sf::Sprite& e2) const
	{
		sf::IntRect bounds1(static_cast<sf::IntRect>(e1.getGlobalBounds()));
		sf::IntRect bounds2(static_cast<sf::IntRect>(e2.getGlobalBounds()));
		sf::IntRect intersection;

		if (bounds1.intersects(bounds2, intersection))
		{
			const sf::Transform& inverse1(e1.getInverseTransform());
			const sf::Transform& inverse2(e2.getInverseTransform());
			
			const sf::Image image1 = e1.getTexture()->copyToImage();
			const sf::Image image2 = e2.getTexture()->copyToImage();

			const sf::Vector2u imgSize1(image1.getSize());
			const sf::Vector2u imgSize2(image2.getSize());

			const sf::Uint8* pixels1 = image1.getPixelsPtr();
			const sf::Uint8* pixels2 = image2.getPixelsPtr();
			
			sf::Vector2f vec1, vec2;
			int xMax = intersection.left + intersection.width;
			int yMax = intersection.top + intersection.height;
			
			for (int i = intersection.left; i < xMax; i++)
				for (int j = intersection.top; j < yMax; j++) 
				{
				 	vec1 = inverse1.transformPoint(i, j);
				 	vec2 = inverse2.transformPoint(i, j);

					int idx1 = (static_cast<int>(vec1.x) + static_cast<int>(vec1.y) * imgSize1.x) * 4 + 3;
				 	int idx2 = (static_cast<int>(vec2.x) + static_cast<int>(vec2.y) * imgSize2.x) * 4 + 3;
				
					if (vec1.x > 0 && vec1.y > 0 && vec2.x > 0 && vec2.y > 0 &&
					 	vec1.x < imgSize1.x && vec1.y < imgSize1.y &&
					 	vec2.x < imgSize2.x && vec2.y < imgSize2.y &&
						pixels1[idx1] > 0 && pixels2[idx2] > 0)
					 	return true;
				}
		}
		return false;
	}

	// Public Method(s)
		// Check Collision
	bool CollisionHandler::checkCollision(const sf::Sprite& e1, const sf::Sprite& e2,
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
}