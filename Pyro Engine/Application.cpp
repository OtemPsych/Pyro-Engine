#include "Application.h"

#include <SFML/Window/Event.hpp>

namespace pyro
{
	Application::Application(sf::VideoMode VMode, const std::string& title, sf::Uint32 style,
							 const sf::ContextSettings& settings)
		: mWindow(VMode, title, style, settings)
		, mStateStack(mWindow)
		, mFPS(sf::seconds(1.f / 60.f))
		, mClearScreen(true)
	{
	}

	void Application::processEvents()
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			mStateStack.handleEvent(event);
			if (mStateStack.isEmpty())
				mWindow.close();
		}
	}

	void Application::update()
	{
		mStateStack.update(mFPS);
	}
		
	void Application::render()
	{
		if (mClearScreen)
			mWindow.clear();
		mStateStack.draw();
		mWindow.display();
	}

	void Application::run()
	{
		sf::Clock clock;
		sf::Time TimeSinceLastUpdate = sf::Time::Zero;
		while (mWindow.isOpen())
		{
			processEvents();
			TimeSinceLastUpdate += clock.restart();
			while (TimeSinceLastUpdate > mFPS)
			{
				TimeSinceLastUpdate -= mFPS;
				processEvents();
				update();
			}
			render();
		}
	}

	void Application::pushState(StateID::ID id)
	{
		mStateStack.pushState(id);
	}
}