namespace pyro
{
	// Public Method(s)
		// Register State
	template <typename T>
	void StateStack::registerState(StateID::ID stateID)
	{
		mFactories[stateID] = [this] {
			return StatePtr(new T(this, mWindow));
		};
	}
}