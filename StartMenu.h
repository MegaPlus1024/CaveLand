#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <string>

using namespace std;
using namespace sf;

class StartMenu {
private:
	SoundBuffer buffer;

	string *state;

    int winSizex, winSizey;

public:
	Button* start, * exit;
	Music startMenuTheme;

    Image mImage;
    Texture mTexture;
    Sprite background;

	StartMenu(const Vector2f& winSize_);

	StartMenu(string* state, const Vector2f& winSize_);

	void updateButtonStart(Event event, RenderWindow& window);

    void setBackground(string path_);

	void update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time);

	void draw(RenderWindow& window);
};

