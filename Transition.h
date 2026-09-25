#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
#include <string>

using namespace std;
using namespace sf;

class Transition {
public:
    RectangleShape* body;
    Collider* collider;

    string nextlevel;

    Vector2f positionStart;

    Transition(Vector2f borderPosition, Vector2f borderSize, string nextlevel_, Vector2f positionStart_);

    bool CheckCollision(Collider *other, Vector2f &direction);


    void draw(RenderWindow &window);
};