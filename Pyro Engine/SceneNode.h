#ifndef SceneNode_H_
#define SceneNode_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>

namespace pyro
{
	class SceneNode : public sf::Transformable, public sf::Drawable,
					  private sf::NonCopyable
	{
	private:
		// Private Typedef(s)
		using NodePtr = std::unique_ptr<SceneNode>;
	private:
		// Private Member(s)
		std::vector<NodePtr> mChildren;
		SceneNode*			 mParent;

	private:
		// Private Method(s)
		virtual void updateCurrent(sf::Time dt);
		void		 updateChildren(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void		 drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Transform getWorldTransform() const;
	public:
		// Constructor(s) | Destructor
		SceneNode();
		virtual ~SceneNode();
		// Public Method(s)
		void	attachChild(NodePtr child);
		NodePtr detachChild(const SceneNode& node);

		void update(sf::Time dt);

		virtual void centerOrigin();

		sf::Vector2f getWorldPosition() const;
	};
}
#endif