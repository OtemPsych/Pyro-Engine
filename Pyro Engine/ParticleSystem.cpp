#include "ParticleSystem.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace pyro
{
	// Constructor(s)
		// Constructor 1
	ParticleSystem::ParticleSystem(const Particle& prime, const sf::Texture* texture)
		: mPrimeParticle(new Particle(prime))
		, mTexture(texture)
		, mMaxParticles(0)
		, mVertexArray(sf::TrianglesFan)
	{
	}

	// Private Method(s)
		// Compute Vertices
	void ParticleSystem::computeVertices() const
	{
		sf::Vector2f size(mTexture == nullptr ? sf::Vector2f(30.f, 30.f) 
											  : static_cast<sf::Vector2f>(mTexture->getSize()));
		sf::Vector2f half = size / 2.f;

		mVertexArray.clear();

		for (const Particle& particle : mParticles)
		{
			sf::Vector2f pos = particle.position;
			sf::Color c = particle.color;
			float ratio = particle.lifetime.asSeconds() 
						/ mPrimeParticle->lifetime.asSeconds();
			c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

			addVertex(pos.x - half.x, pos.y - half.y, 0.f,	  0.f,	  c);
			addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f,	  c);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, c);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f,	  size.y, c);
		}
	}
		// Add Particle
	void ParticleSystem::addParticle()
	{
		mParticles.push_back(Particle(*mPrimeParticle));
	}
		// Add Vertex
	void ParticleSystem::addVertex(float x, float y, float tu, float tv, const sf::Color& color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(x, y);
		vertex.texCoords = sf::Vector2f(tu, tv);
		vertex.color = color;

		mVertexArray.append(vertex);
	}
		// Draw
	void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = mTexture;
		target.draw(mVertexArray, states);
	}

	// Public Method(s)
		// Update
	void ParticleSystem::update(sf::Time dt)
	{
		try {
			if (mEmitterActive && mPrimeParticle != nullptr
				&& (mParticles.size() < mMaxParticles || mMaxParticles == 0))
				addParticle();

			for (unsigned i = 0; i < mParticles.size(); i++) 
			{
				mAffector(mParticles[i], dt);
				if ((mParticles[i].lifetime -= dt) <= sf::Time::Zero)
					mParticles.erase(mParticles.begin() + i);
			}

			computeVertices();
		}
		catch (std::exception& e) {
			std::cout << "\nEXCEPTION: " << e.what() 
					  << "\npyro::ParticleSystem - The Affector hasn't been set!\n";
			std::cin.get();
			exit(EXIT_FAILURE);
		}
	}
		// Set Prime Particle
	void ParticleSystem::setPrimeParticle(const Particle& prime)
	{
		mPrimeParticle = std::unique_ptr<Particle>(new Particle(prime));
	}
}