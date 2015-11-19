#include "SceneNode.h"

#include <cassert>

namespace pyro
{
	// Constructor(s)
		// Default
	SceneNode::SceneNode()
		: mParent(nullptr)
	{
	}
	// Destructor
	SceneNode::~SceneNode()
	{
	}

	// Private Method(s)
		// Update Current
	void SceneNode::updateCurrent(sf::Time dt)
	{
	}
		// Update Children
	void SceneNode::updateChildren(sf::Time dt)
	{
		for (auto& child : mChildren)
			child->update(dt);
	}
		// Draw
	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		drawCurrent(target, states);
		drawChildren(target, states);
	}
		// Draw Current
	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
		// Draw Children
	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& child : mChildren)
			child->draw(target, states);
	}
		// Get World Transform
	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const auto* node = this; node != nullptr; node = node->mParent)
			transform *= node->getTransform();

		return transform;
	}

	// Public Method(s)
		// Attach Child
	void SceneNode::attachChild(NodePtr child)
	{
		child->mParent = this;
		mChildren.push_back(std::move(child));
	}
		// Detach Child
	SceneNode::NodePtr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(mChildren.begin(), mChildren.end(),
			[&](NodePtr& p) { return p.get() == &node; });

		assert(found != mChildren.end());

		NodePtr result = std::move(*found);
		result->mParent = nullptr;
		mChildren.erase(found);
		return result;
	}
		// Update
	void SceneNode::update(sf::Time dt)
	{
		updateCurrent(dt);
		updateChildren(dt);
	}
		// Center Origin
	void SceneNode::centerOrigin()
	{
	}
		// Get World Position
	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}
}