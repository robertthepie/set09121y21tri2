//ship.cpp
#include "Ship.h"
#include "game.h"
#include "Bullet.h"
using namespace sf;
using namespace std;

/*
** Ship
*/

// constructors
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

// functions
void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


void Ship::Explode() {
    setTextureRect(IntRect(128, 32, 32, 32));
    _exploded = true;
}

bool Ship::is_exploded() const {
    return _exploded;
}

/*
** Invader
*/

// variables
bool Invader::direction;
float Invader::speed;


// constructor
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

// functions
void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            if (typeid(*(ships[i])) == typeid(Invader))
                ships[i]->move(0, 24);
        }
    }
    static float firetime = 0.0f;
    firetime -= dt;
    if (firetime <= 0 && rand() % 100 == 0) {
        Bullet::Fire(getPosition(), true);
        firetime = 4.0f + (rand() % 60);
    }
}


/*
** Player
*/

//ship.cpp
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    Ship::Update(dt);
    //Move left
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        if (getPosition().x > 0)
        move(-150 * dt, 0);
    }
    //Move Right
    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
        if (getPosition().x < gameWidth - 32)
        move(150 * dt, 0);
    }

    static float firetime = 0.0f;
    firetime -= dt;
    if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
        Bullet::Fire(getPosition(), false);
        firetime = 0.7f;
    }
}

