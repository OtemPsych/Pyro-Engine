#ifndef StateStack_H_
#define StateStack_H_

#include "State.h"

#include <memory>
#include <map>
#include <functional>

namespace pyro
{
	class StateStack : private sf::NonCopyable
	{
	public:
		enum Action { Push, Pop, Clear };
	private:
		using StatePtr = std::unique_ptr<State>;

		struct PendingChange {
			explicit PendingChange(Action action, StateID::ID stateID = StateID::None);

			Action		action;
			StateID::ID stateID;
		};
	private:
		std::vector<std::pair<StateID::ID, StatePtr>>	 mStack;
		std::vector<PendingChange>						 mPendingList;

		std::map<StateID::ID, std::function<StatePtr()>> mFactories;
		sf::RenderWindow&								 mWindow;

	private:
		StatePtr createState(StateID::ID stateID);
		void	 applyPendingChanges();
	public:
		explicit StateStack(sf::RenderWindow& window);
	public:
		void handleEvent(const sf::Event& event);
		void update(sf::Time dt);
		void draw();

		void pushState(StateID::ID stateID);
		void popState();
		void removeState(StateID::ID stateID);
		void clearStates();

		const State* getState(StateID::ID stateID);

		template <typename T>
		void registerState(StateID::ID stateID);

		inline bool isEmpty() const { return mStack.empty(); }
	};
}
#include "StateStack.inl"
#endif