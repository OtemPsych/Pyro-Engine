#ifndef Application_H_
#define Application_H_

#include "StateStack.h"

namespace pyro
{
	class Application : private sf::NonCopyable
	{
	private:
		sf::RenderWindow mWindow;
		StateStack		 mStateStack;

		sf::Time		 mFPS;

		bool			 mClearScreen;

	private:
		void processEvents();
		void update();
		void render();
	public:
		Application(sf::VideoMode VMode, const std::string& title, sf::Uint32 style = sf::Style::Default,
					const sf::ContextSettings& settings = sf::ContextSettings());
	public:
		void run();
		void pushState(StateID::ID id);
		template <typename T>
		void registerState(StateID::ID id);

		inline void setFPS(float fps) { mFPS = sf::seconds(1.f / fps); }
		inline void setClearScreen(bool state) { mClearScreen = state; }
	};

	template <typename T>
	void Application::registerState(StateID::ID id)
	{
		mStateStack.registerState<T>(id);
	}
}
#endif