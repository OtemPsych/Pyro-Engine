#ifndef SoundPlayer_H_
#define SoundPlayer_H_

#include "../ResourceHolder.h"

#include <SFML/Audio/Sound.hpp>

#include <list>

namespace pyro
{
	template <typename SoundID>
	class SoundPlayer : private sf::NonCopyable
	{
	private:
		struct SoundCoords
		{
			float listenerZ,
				attenuation,
				minDistance2D,
				minDistance3D;
		};
	private:
		SoundBufferHolder<SoundID> mSoundBuffers;
		std::list<sf::Sound>       mSounds;
		SoundCoords                mSoundCoords;

	private:
		void removeStoppedSounds();
		void setupSoundCoords();
	public:
		SoundPlayer();
	public:
		void play(SoundID effect);
		void play(SoundID effect, sf::Vector2f pos, float volume = 100.f);

		void loadEffect(SoundID effect, const std::string& filename);

		void setListenerPosition(sf::Vector2f pos);
		sf::Vector2f getListenerPosition() const;
	};
}
#include "SoundPlayer.inl"
#endif