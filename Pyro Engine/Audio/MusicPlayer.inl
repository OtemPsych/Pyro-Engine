namespace pyro
{
	template <typename MusicID>
	MusicPlayer<MusicID>::MusicPlayer()
		: mVolume(100.f)
	{
	}

	template <typename MusicID>
	void MusicPlayer<MusicID>::play(MusicID theme)
	{
		auto found = mFilenames.find(theme);
		assert(found != mFilenames.end());

		try {
			if (!mMusic.openFromFile(found->second))
				throw std::runtime_error("MusicPlayer::play - Couldn't load " + found->second);
		}
		catch (std::runtime_error& e) {
			std::cout << "\nEXCEPTION: " << e.what() << std::endl;
			return;
		}

		mMusic.setVolume(mVolume);
		mMusic.setLoop(true);
		mMusic.play();
	}

	template <typename MusicID>
	void MusicPlayer<MusicID>::stop()
	{
		mMusic.stop();
	}

	template <typename MusicID>
	void MusicPlayer<MusicID>::loadTheme(MusicID theme, const std::string& filename)
	{
		mFilenames.insert(std::make_pair(theme, filename));
	}

	template <typename MusicID>
	void MusicPlayer<MusicID>::pause(bool flag)
	{
		flag ? mMusic.pause() : mMusic.play();
	}
}