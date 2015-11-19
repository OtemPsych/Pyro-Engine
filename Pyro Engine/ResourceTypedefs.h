#ifndef ResourceTypedefs_H_
#define ResourceTypedefs_H_

#include "ResourceHolder.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace pyro
{
	template <typename T>
	using TextureHolder		= ResourceHolder<T, sf::Texture>;

	template <typename T>
	using ImageHolder		= ResourceHolder<T, sf::Image>;

	template <typename T>
	using FontHolder		= ResourceHolder<T, sf::Font>;

	template <typename T>
	using SoundBufferHolder = ResourceHolder<T, sf::SoundBuffer>;
}
#endif