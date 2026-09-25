#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Geometry.h"
#include "Animation.h"
#include "Collider.h"
#include "Entity.h"
using namespace std;
using namespace sf;

class Player;

class Turtle : public Entity {
public:
    Turtle(Vector2f Position, Vector2f size, float offset, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime);

    //обновление движения
    void updateMove(float time, Player* Player);

    //обработка коллизий
    void OnCollision(sf::Vector2f direction);
};