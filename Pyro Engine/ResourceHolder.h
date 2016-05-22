#ifndef ResourceHolder_H_
#define ResourceHolder_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <map>

namespace pyro
{
	template <typename ID, typename Res>
	class ResourceHolder : private sf::NonCopyable
	{
	private:
		std::map<ID, Res> mResourceMap;

	private:
		void insertResource(ID id, const Res& res);
	public:
		void load(ID id, const std::string& filename);
		Res&       get(ID id);
		const Res& get(ID id) const;
	};

	template <typename ID>
	using TextureHolder     = ResourceHolder<ID, sf::Texture>;
	template <typename ID>
	using ImageHolder       = ResourceHolder<ID, sf::Image>;
	template <typename ID>
	using FontHolder        = ResourceHolder<ID, sf::Font>;
	template <typename ID>
	using SoundBufferHolder = ResourceHolder<ID, sf::SoundBuffer>;
}
#include "ResourceHolder.inl"
#endif