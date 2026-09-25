#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    void update(int row, float deltaTime, bool faceRight);

    void update(int row, float deltaTime, bool faceRight, pair<int, int> start);

    void reset();

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};