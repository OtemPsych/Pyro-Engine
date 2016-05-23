#include "ParticleSystem.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace pyro
{
	ParticleSystem::ParticleSystem(sf::PrimitiveType primType, unsigned maxParticles,
		                           const sf::Texture* texture)
		: mMaxParticles(maxParticles)
		, mVertexArray(primType)
		, mTexture(texture)
		, mEmitterActive(false)
		, mEmitterPos()
		, mOriginalParticleLifetime(sf::Time::Zero)
		, mInitializer(nullptr)
		, mAffector(nullptr)
	{
	}

	void ParticleSystem::computeVertices() const
	{
		if (mOriginalParticleLifetime != sf::Time::Zero && !mParticles.empty())
		{
			sf::Vector2f size(mParticles.front().size);
			sf::Vector2f half = size / 2.f;

			mVertexArray.clear();

			for (const Particle& particle : mParticles)
			{
				sf::Vector2f pos = particle.position;
				sf::Color c = particle.color;
				float ratio = particle.lifetime.asSeconds() / mOriginalParticleLifetime.asSeconds();
				c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

				addVertex(pos.x - half.x, pos.y - half.y, 0.f,    0.f,    c);
				addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f,    c);
				addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, c);
				addVertex(pos.x - half.x, pos.y + half.y, 0.f,    size.y, c);
			}
		}
		else
			std::cout << "\n\nA particle's lifetime can't be set at 0\n\n";
	}

	void ParticleSystem::addParticle()
	{
		mParticles.push_back(std::move((*mInitializer)()));
		mParticles.back().position = mEmitterPos;
		mParticles.back().originalLifetime = &mOriginalParticleLifetime;
	}

	void ParticleSystem::addVertex(float x, float y, float tu, float tv, const sf::Color& color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(x, y);
		vertex.texCoords = sf::Vector2f(tu, tv);
		vertex.color = color;

		mVertexArray.append(std::move(vertex));
	}

	void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = mTexture;
		target.draw(mVertexArray, states);
	}

	void ParticleSystem::update(sf::Time dt)
	{
		if (mEmitterActive && mInitializer && mAffector)
		{
			if (mParticles.size() < mMaxParticles || mMaxParticles == 0)
				addParticle();

			for (auto& particle : mParticles) {
				(*mAffector)(particle, dt);
				particle.lifetime -= dt;
			}
			if (!mParticles.empty() && mParticles.front().lifetime <= sf::Time::Zero)
				mParticles.erase(mParticles.begin());

			computeVertices();
		}
		else
			std::cout << "\n\nUnable to update ParticleSystem\n"
			          << "3 possible causes:\n"
			          << "  - The Emitter hasn't been activated\n"
			          << "  - The Initializer hasn't been set\n"
			          << "  - The Affector hasn't been set\n\n";
	}

	void ParticleSystem::setInitializer(const std::function<Particle()>& initializer)
	{
		mInitializer = std::make_unique<std::function<Particle()>>(std::move(initializer));
		mOriginalParticleLifetime = (*mInitializer)().lifetime;
	}

	void ParticleSystem::setAffector(const std::function<void(Particle&, sf::Time)>& affector)
	{
		mAffector = std::make_unique<std::function<void(Particle&, sf::Time)>>(std::move(affector));
	}
}