#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
using namespace std;
using namespace sf;


class text {
private:
    string str;

    Font font;

public:
    Text txt;

    text();

    text(string strName);

    virtual void sleditForSprite(Sprite& s, float x, float y);

    void getChislo(float n);

    void setString(string name);

    virtual void setPosition(float x, float y);

    virtual void setPosition(Vector2f pos);

    virtual void setOriginCenter();

    void setFillTextColor(float R, float G1, float B);

    void setCharacterSize(float a);

    virtual void draw(RenderWindow& window);
};

