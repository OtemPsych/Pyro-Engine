#include "Text.h"
#include "ResourceHolder.h"
#include "ParticleSystem.h"
#include "Math.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

int main()
{
	srand(static_cast<unsigned>(time(0)));

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Default, sf::ContextSettings(0, 0, 16));
	window.setFramerateLimit(144);

	using namespace pyro;
	using namespace utils;

	enum class FontType { Basic };
	FontHolder<FontType> fontHolder;
	fontHolder.load(FontType::Basic, "C:/Users/glegl/Documents/Visual Studio 2013/Projects/2016 Projects/C++ & SFML Projects/Age of War/Age of War/Assets/Fonts/Menu.ttf");


	Text text;
	text.activateShadow(true);
	text.setFont(fontHolder.get(FontType::Basic));
	text.setString("Lorem Ipsum");
	text.setCharacterSize(40);
	text.setTextColor(sf::Color::Black);
	text.setShadowOffset(1.8f, 1.8f);
	text.setShadowColor(sf::Color(0, 0, 0, 100));
	text.setPosition(0.f, 0.f);

	Text text2;
	text2.loadFontFromFile("C:/Users/glegl/Documents/Visual Studio 2013/Projects/2016 Projects/C++ & SFML Projects/Age of War/Age of War/Assets/Fonts/Menu.ttf");
	text2.setString("Lorem Ipsum");
	text2.setCharacterSize(40);
	text2.setTextColor(sf::Color::Black);
	text2.setPosition(0.f, 100.f);

	Text text3;
	text3.activateShadow(true);
	text3.loadFontFromFile("C:/Users/glegl/Documents/Visual Studio 2013/Projects/2016 Projects/C++ & SFML Projects/Age of War/Age of War/Assets/Fonts/Menu.ttf");
	text3.setString("Lorem Ipsum");
	text3.setCharacterSize(40);
	text3.setTextColor(sf::Color::Black);
	text3.setShadowOffset(2.f, 2.f);
	text3.setShadowColor(sf::Color(102, 153, 153, 150));
	text3.setPosition(0.f, 200.f);

	sf::Texture ianTexture;
	ianTexture.loadFromFile("C:/Users/glegl/Pictures/Ian/Ian1.jpg");

	ParticleSystem particleSystem(sf::Quads, 5000);
	particleSystem.activateEmitter(true);
	particleSystem.setInitializer([]()
	{
		Particle particle;
		particle.size = sf::Vector2f(2.f, 3.5f);
		float speed = 350.f;
		float min = -135.f, max = -45.f;
		float angle = pyro::math::toRadians(std::rand() / (RAND_MAX / (max - min)) + min);
		particle.velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
		particle.acceleration = sf::Vector2f(0.f, 5.f);
		int randValue = rand() % 11;
		particle.color = sf::Color(std::min(randValue * 25, 255), std::min(randValue * 10, 255) + 153, 255);
		particle.lifetime = sf::seconds(2.5f);

		return std::move(particle);
	});
	particleSystem.setAffector([](Particle& particle, sf::Time dt)
	{
		particle.velocity += particle.acceleration;
		particle.position += particle.velocity * dt.asSeconds();
	});

	sf::Clock clock;
	const sf::Time TimePerFrame(sf::seconds(1.f / 60.f));
	sf::Time TimeSinceLastUpdate(sf::Time::Zero);
	while (window.isOpen())
	{
		TimeSinceLastUpdate += clock.restart();
		while (TimeSinceLastUpdate > TimePerFrame)
		{
			TimeSinceLastUpdate -= TimePerFrame;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			particleSystem.setEmitterPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			particleSystem.update(TimePerFrame);
		}
		window.clear(sf::Color::Black);
		window.draw(text);
		window.draw(text2);
		window.draw(text3);
		window.draw(particleSystem);
		window.display();
	}

	return 0;
}