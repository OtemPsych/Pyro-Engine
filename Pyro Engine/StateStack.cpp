#include "StateStack.h"

#include <cassert>
#include <iostream>

namespace pyro
{
	StateStack::PendingChange::PendingChange(Action action, StateID::ID stateID)
		: action(action)
		, stateID(stateID)
	{
	}

	StateStack::StateStack(sf::RenderWindow& window)
		: mWindow(window)
	{
	}

	StateStack::StatePtr StateStack::createState(StateID::ID stateID)
	{
		auto found = mFactories.find(stateID);
		assert(found != mFactories.end());

		return found->second();
	}

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

	void StateStack::handleEvent(const sf::Event& event)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
			if (!(*itr).second->handleEvent(event))
				break;

		applyPendingChanges();
	}

	void StateStack::update(sf::Time dt)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
			if (!(*itr).second->update(dt))
				break;

		applyPendingChanges();
	}

	void StateStack::draw()
	{
		for (const auto& state : mStack)
			state.second->draw();
	}

	void StateStack::pushState(StateID::ID stateID)
	{
		mPendingList.push_back(PendingChange(Push, stateID));
	}

	void StateStack::popState()
	{
		mPendingList.push_back(PendingChange(Pop));
	}

	void StateStack::removeState(StateID::ID stateID)
	{
		for (unsigned i = 0; i < mStack.size(); i++)
			if (mStack[i].first == stateID)
				mStack.erase(mStack.begin() + i);
	}

	void StateStack::clearStates()
	{
		mPendingList.push_back(PendingChange(Clear));
	}

	const State* StateStack::getState(StateID::ID stateID)
	{
		for (const auto& state : mStack)
			if (state.first == stateID)
				return state.second.get();

		return nullptr;
	}
}