#include "StateStack.h"

#include <cassert>

namespace pyro
{
	// Constructor(s)
		// Constructor 1
	StateStack::StateStack(sf::RenderWindow& window)
		: mWindow(window)
	{
	}

	// Private Method(s)
		// Create State
	StateStack::StatePtr StateStack::createState(StateID::ID stateID)
	{
		auto found = mFactories.find(stateID);
		assert(found != mFactories.end());

		return found->second();
	}
		// Apply Pending Changes
	void StateStack::applyPendingChanges()
	{
		for (const auto& change : mPendingList)
			switch (change.action)
			{
			case Push:
				mStack.push_back(createState(change.stateID));
				break;

			case Pop:
				mStack.pop_back();
				break;

			case Clear:
				mStack.clear();
				break;
			}

		mPendingList.clear();
	}

	// Public Method(s)
		// Handle Event
	void StateStack::handleEvent(const sf::Event& event)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
			if (!(*itr)->handleEvent(event))
				break;

		applyPendingChanges();
	}
		// Update
	void StateStack::update(sf::Time dt)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
			if (!(*itr)->update(dt))
				break;

		applyPendingChanges();
	}
		// Draw
	void StateStack::draw()
	{
		for (StatePtr& state : mStack)
			state->draw();
	}
		// Push State
	void StateStack::pushState(StateID::ID stateID)
	{
		mPendingList.push_back(PendingChange(Push, stateID));
	}
		// Pop State
	void StateStack::popState()
	{
		mPendingList.push_back(PendingChange(Pop));
	}
		// Clear States
	void StateStack::clearStates()
	{
		mPendingList.push_back(PendingChange(Clear));
	}

	// Pending Change Constructor
	StateStack::PendingChange::PendingChange(Action action, StateID::ID stateID)
		: action(action)
		, stateID(stateID)
	{
	}
}