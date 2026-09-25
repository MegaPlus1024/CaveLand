#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <string>

using namespace std;
using namespace sf;

class PauseMenu {
private:
    SoundBuffer buffer;

    string *state;

    RectangleShape* pad;

    int winSizex, winSizey;

public:
    Vector2f resumepos, exitpos;
    Button* resume, * exit;
    Music PauseMenuTheme;

    PauseMenu(const Vector2f& winSize_);

    PauseMenu(string* state, const Vector2f& winSize_);

    void updateButtonStart(Event event, RenderWindow& window, View& view);

    void setBackground(string path_);

    void update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time);

    void draw(RenderWindow& window);
};

