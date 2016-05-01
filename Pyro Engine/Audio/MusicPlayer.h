#ifndef MusicPlayer_H_
#define MusicPlayer_H_

#include <SFML/Audio/Music.hpp>

#include <map>

namespace pyro
{
	template <typename MusicID>
	class MusicPlayer : private sf::NonCopyable
	{
	private:
		sf::Music                      mMusic;
		std::map<MusicID, std::string> mFilenames;
		float                          mVolume;

	public:
		MusicPlayer();
	public:
		void play(MusicID theme);
		void stop();

		void loadTheme(MusicID theme, const std::string& filename);
		void pause(bool flag);

		inline void setVolume(float volume) { mVolume = volume; }
	};
}
#include "MusicPlayer.inl"
#endif