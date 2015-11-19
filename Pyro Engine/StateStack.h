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
		// Public Enum(s)
		enum Action { Push, Pop, Clear };
	private:
		// Private Typedef(s)
		using StatePtr = std::unique_ptr<State>;
		// Private Struct(s)
		struct PendingChange {
			explicit PendingChange(Action action, StateID::ID stateID = StateID::None);

			Action		action;
			StateID::ID stateID;
		};
	private:
		// Private Member(s)
		std::vector<StatePtr>							 mStack;
		std::vector<PendingChange>						 mPendingList;

		std::map<StateID::ID, std::function<StatePtr()>> mFactories;
		sf::RenderWindow&								 mWindow;

	private:
		// Private Method(s)
		StatePtr createState(StateID::ID stateID);
		void	 applyPendingChanges();
	public:
		// Constructor(s)
		explicit StateStack(sf::RenderWindow& window);
		// Public Method(s)
		void handleEvent(const sf::Event& event);
		void update(sf::Time dt);
		void draw();

		void pushState(StateID::ID stateID);
		void popState();
		void clearStates();

		template <typename T>
		void registerState(StateID::ID stateID);

		inline bool isEmpty() const { return mStack.empty(); }
	};
}
#include "StateStack.inl"
#endif