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

		sf::Time		 mTimePerFrame;

	private:
		void processEvents();
		void update();
		void render();
	public:
		Application(sf::VideoMode VMode, const std::string& title, sf::Uint32 style = sf::Style::Default,
					const sf::ContextSettings& settings = sf::ContextSettings());
	public:
		void run();
		void setFPS(unsigned fps);

		void pushState(StateID::ID id);
		template <typename T>
		void registerState(StateID::ID id);

	};

	template <typename T>
	void Application::registerState(StateID::ID id)
	{
		mStateStack.registerState<T>(id);
	}
}
#endif