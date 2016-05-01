#ifndef State_H_
#define State_H_

#include "StateIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace pyro
{
	class StateStack;
	class State : private sf::NonCopyable
	{
	private:
		StateStack&		  mStack;
	protected:
		sf::RenderWindow& mWindow;

	protected:
		void requestStatePush(StateID::ID stateID);
		void requestStatePop();
		void requestStateRemoval(StateID::ID stateID);
		void requestStateClear();

		virtual void setupResources();
	public:
		State(StateStack& stack, sf::RenderWindow& window);
		virtual ~State();
	public:
		virtual bool handleEvent(const sf::Event& event);
		virtual bool update(sf::Time dt);
		virtual void draw();
	};
}
#endif