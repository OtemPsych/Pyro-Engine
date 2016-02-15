#include "State.h"
#include "StateStack.h"

namespace pyro
{
	// Constructor(s)
	// Constructor 1
	State::State(StateStack& stack, sf::RenderWindow& window)
		: mStack(stack)
		, mWindow(window)
	{
	}
	// Destructor
	State::~State()
	{
	}

	// Protected Method(s)
	// Request State Push
	void State::requestStatePush(StateID::ID stateID)
	{
		mStack.pushState(stateID);
	}
	// Request State Pop
	void State::requestStatePop()
	{
		mStack.popState();
	}
	// Request State Clear
	void State::requestStateClear()
	{
		mStack.clearStates();
	}

	// Public Method(s)
	// Handle Event
	bool State::handleEvent(const sf::Event& event)
	{
		return true;
	}
	// Update
	bool State::update(sf::Time dt)
	{
		return true;
	}
}