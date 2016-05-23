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
		sf::Vector2f size;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Color	 color;
		sf::Time	 lifetime;
		sf::Time*    originalLifetime;
	};

	class ParticleSystem : public sf::Drawable
	{
	private:
		std::vector<Particle>                                     mParticles;
		unsigned								                  mMaxParticles;
		mutable sf::VertexArray					                  mVertexArray;
		const sf::Texture*						                  mTexture;
												                  
		bool									                  mEmitterActive;
		sf::Vector2f                                              mEmitterPos;

		sf::Time                                                  mOriginalParticleLifetime;
		std::unique_ptr<std::function<Particle()>>                mInitializer;
		std::unique_ptr<std::function<void(Particle&, sf::Time)>> mAffector;

	private:
		void computeVertices() const;
		void addParticle();
		void addVertex(float x, float y, float tu, float tv, const sf::Color& color) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		explicit ParticleSystem(sf::PrimitiveType primType = sf::Quads, unsigned maxParticles = 0,
			                    const sf::Texture* texture = nullptr);
	public:
		void update(sf::Time dt);

		void setInitializer(const std::function<Particle()>& initializer);
		void setAffector(const std::function<void(Particle&, sf::Time)>& affector);

		inline void setMaxParticles(unsigned max = 0) { mMaxParticles = max; }
		inline void setTexture(const sf::Texture* texture) { mTexture = texture; }
		inline void activateEmitter(bool state = true) { mEmitterActive = state; }
		inline void setEmitterPosition(sf::Vector2f pos) { mEmitterPos = pos; }
	};
}
#endif