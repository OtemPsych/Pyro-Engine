#include <SFML/Audio/Listener.hpp>

namespace pyro
{
	template <typename SoundID>
	SoundPlayer<SoundID>::SoundPlayer()
	{
		sf::Listener::setDirection(0.f, 0.f, -1.f);
		setupSoundCoords();
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::removeStoppedSounds()
	{
		mSounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::setupSoundCoords()
	{
		mSoundCoords.listenerZ = 300.f;
		mSoundCoords.attenuation = 8.f;
		mSoundCoords.minDistance2D = 200.f;
		mSoundCoords.minDistance3D = sqrt(pow(mSoundCoords.minDistance2D, 2) + pow(mSoundCoords.listenerZ, 2));
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::play(SoundID effect)
	{
		play(effect, getListenerPosition());
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::play(SoundID effect, sf::Vector2f pos, float volume)
	{
		removeStoppedSounds();

		mSounds.emplace_back(sf::Sound());
		sf::Sound& sound(mSounds.back());

		sound.setBuffer(mSoundBuffers.get(effect));
		sound.setPosition(pos.x, -pos.y, 0.f);
		sound.setAttenuation(mSoundCoords.attenuation);
		sound.setMinDistance(mSoundCoords.minDistance3D);
		sound.setVolume(volume);

		sound.play();
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::loadEffect(SoundID effect, const std::string& filename)
	{
		mSoundBuffers.load(effect, filename);
	}

	template <typename SoundID>
	void SoundPlayer<SoundID>::setListenerPosition(sf::Vector2f pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, mSoundCoords.listenerZ);
	}

	template <typename SoundID>
	sf::Vector2f SoundPlayer<SoundID>::getListenerPosition() const
	{
		sf::Vector3f pos(sf::Listener::getPosition());
		return sf::Vector2f(pos.x, -pos.y);
	}
}