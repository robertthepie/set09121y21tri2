#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

extern std::unique_ptr<Player>player;