#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

class FinishMenu {
private:
    SoundBuffer buffer;

    string *state;

    int winSizex, winSizey;

public:
    Button* continue_, *score;
    Music FinishMenuTheme;

    Image mImage;
    Texture mTexture;
    Sprite background;

    FinishMenu(const Vector2f& winSize_);

    FinishMenu(string* state, const Vector2f& winSize_);

    void updateButtonStart(Event event, RenderWindow& window);

    void setBackground(string path_);

    void update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time);

    void draw(RenderWindow& window);
};

