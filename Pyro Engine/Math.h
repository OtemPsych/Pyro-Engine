#ifndef Math_H_
#define Math_H_

#define Math_PI 3.14159265f

#include <SFML/System/Vector2.hpp>

#include <cmath>

namespace pyro
{
	namespace math
	{
		inline float toDegrees(float radians)
		{
			return radians * 180.f / Math_PI;
		}

		inline float toRadians(float degrees)
		{
			return degrees * Math_PI / 180.f;
		}

		inline float getHypotenuse(sf::Vector2f vec)
		{
			return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		}

		inline sf::Vector2f normalizeVector(sf::Vector2f vec)
		{
			return vec / getHypotenuse(vec);
		}
	}
}
#endif