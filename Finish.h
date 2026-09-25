#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
#include <string>

using namespace std;
using namespace sf;

class Finish {
private:
    Image mImage;
    Texture mTexture;

    Vector2f mPosition, mSize;

public:
    Sprite mSprite;

    RectangleShape* body;
    Collider* collider;

    Finish(Vector2f borderPosition, Vector2f borderSize);

    Finish(Vector2f borderPosition, Vector2f borderSize, string path_);

    void setTexture(string path_);

    bool CheckCollision(Collider *other, Vector2f &direction);


    void draw(RenderWindow &window);
};