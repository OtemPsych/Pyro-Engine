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
		// Private Member(s)
		StateStack&		  mStack;
		sf::RenderWindow& mWindow;

	protected:
		// Protected Method(s)
		void requestStatePush(StateID::ID stateID);
		void requestStatePop();
		void requestStateClear();

		virtual void setupResources() = 0;
	public:
		// Constructor(s) | Destructor
		State(StateStack& stack, sf::RenderWindow& window);
		virtual ~State();
		// Public Method(s)
		virtual bool handleEvent(const sf::Event& event) = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual void draw() = 0;
	};
}
#endif