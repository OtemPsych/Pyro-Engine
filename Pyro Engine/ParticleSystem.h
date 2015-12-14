#ifndef ParticleSystem_H_
#define ParticleSystem_H_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>
#include <vector>
#include <functional>

namespace pyro 
{
	struct Particle
	{
		sf::Vector2f position;
		sf::Color	 color;
		sf::Time	 lifetime;
	};

	class ParticleSystem : public sf::Drawable
	{
	private:
		// Private Member(s)
		std::unique_ptr<Particle>				 mPrimeParticle;
		std::vector<Particle>					 mParticles;
		unsigned								 mMaxParticles;

		const sf::Texture*						 mTexture;

		mutable sf::VertexArray					 mVertexArray;

		bool									 mEmitterActive;
		std::function<void(Particle&, sf::Time)> mAffector;

	private:
		// Private Method(s)
		void computeVertices() const;
		void addParticle();
		void addVertex(float x, float y, float tu, float tv, const sf::Color& color) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		// Constructor(s)
		ParticleSystem(const Particle& prime, const sf::Texture* texture = nullptr);
		// Public Method(s)
		void update(sf::Time dt);
		void setPrimeParticle(const Particle& prime);

		// 0 for unlimited
		inline void setMaxParticles(unsigned max = 0) { mMaxParticles = max; }

		inline void setTexture(const sf::Texture* texture) { mTexture = texture; }

		inline void activateEmitter(bool state = true) { mEmitterActive = state; }
		inline void setEmitterPosition(sf::Vector2f pos) { mPrimeParticle->position = pos; }

		inline void setAffector(decltype(mAffector) affector) { mAffector = affector; }
	};
}
#endif