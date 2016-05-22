#ifndef Utils_H_
#define Utils_H_

#include <SFML/System/Utf.hpp>

namespace pyro 
{
	namespace utils 
	{
		template <typename T>
		struct Resource
		{
			const T original;
			T       current;

			explicit Resource(T amount);
		};

		enum OriginFlags
		{
			Center  = 0,
			CenterX = 1 << 0,
			CenterY = 1 << 1,
			Left    = 1 << 2,
			Right   = 1 << 3,
			Top     = 1 << 4,
			Bottom  = 1 << 5
		};
		template <class T>
		void setOriginFlags(T& t, sf::Uint32 originFlags);
	}
}
#include "Utils.inl"
#endif