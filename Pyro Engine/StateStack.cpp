#include "StateStack.h"

#include <cassert>
#include <iostream>

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
				mStack.push_back(std::make_pair(change.stateID, createState(change.stateID)));
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
			if (!(*itr).second->handleEvent(event))
				break;

		applyPendingChanges();
	}
		// Update
	void StateStack::update(sf::Time dt)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
			if (!(*itr).second->update(dt))
				break;

		applyPendingChanges();
	}
		// Draw
	void StateStack::draw()
	{
		for (const auto& state : mStack)
			state.second->draw();
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
		// Get State
	const StateStack::StatePtr& StateStack::getState(StateID::ID stateID)
	{
		for (const auto& state : mStack)
			if (state.first == stateID)
				return state.second;
	}

	// Pending Change Constructor
	StateStack::PendingChange::PendingChange(Action action, StateID::ID stateID)
		: action(action)
		, stateID(stateID)
	{
	}
}