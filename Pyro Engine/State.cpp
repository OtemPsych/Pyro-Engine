#include "State.h"
#include "StateStack.h"

namespace pyro
{
	State::State(StateStack& stack, sf::RenderWindow& window)
		: mStack(stack)
		, mWindow(window)
	{
	}

	State::~State()
	{
	}

	void State::requestStatePush(StateID::ID stateID)
	{
		mStack.pushState(stateID);
	}

	void State::requestStatePop()
	{
		mStack.popState();
	}

	void State::requestStateRemoval(StateID::ID stateID)
	{
		mStack.removeState(stateID);
	}

	void State::requestStateClear()
	{
		mStack.clearStates();
	}

	void State::setupResources()
	{
	}

	bool State::handleEvent(const sf::Event& event)
	{
		return true;
	}

	bool State::update(sf::Time dt)
	{
		return true;
	}

	void State::draw()
	{
	}
}