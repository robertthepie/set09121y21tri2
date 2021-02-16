//bullet.h
#pragma once
#include <SFML/Graphics.hpp>

//bullet.h
class Bullet : public sf::Sprite {
public:
	Bullet();
	Bullet(const sf::Vector2f& pos, const bool mode);

	//updates All bullets
	static void Update(const float& dt);
	//Render's All bullets
	static void Render(sf::RenderWindow& window);
	//Chose an inactive bullet and use it.
	static void Fire(const sf::Vector2f& pos, const bool mode);

	~Bullet() = default;

protected:
	// uhh
	sf::IntRect _sprite;
	// newest bullet pointer
	static unsigned char bulletPointer;
	// bullet pool
	static Bullet bullets[256];
	//Called by the static Update()
	void _Update(const float& dt);
	//false=player bullet, true=Enemy bullet
	bool _mode;
};

	