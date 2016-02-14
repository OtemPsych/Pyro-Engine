#ifndef SoundPlayer_H_
#define SoundPlayer_H_

#include "ResourceTypedefs.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

namespace pyro
{
	template <typename SoundID>
	class SoundPlayer : private sf::NonCopyable
	{
	private:
		// Private Struct(s)
		struct SoundCoords {
			float listenerZ,
				  attenuation,
				  minDistance2D,
				  minDistance3D;
		};
	private:
		// Private Member(s)
		SoundBufferHolder<SoundID> mSoundBuffers;
		std::list<sf::Sound>	   mSounds;

		SoundCoords				   mSoundCoords;

	private:
		// Private Method(s)
		void removeStoppedSounds();
		void setupSoundCoords();
	public:
		// Constructor(s)
		SoundPlayer();
		// Public Method(s)
		void play(SoundID effect);
		void play(SoundID effect, sf::Vector2f pos, float volume = 100);

		void loadEffect(SoundID effectID, const std::string& filename);

		void		 setListenerPosition(sf::Vector2f pos);
		sf::Vector2f getListenerPosition() const;
	};
}
#include "SoundPlayer.inl"
#endif