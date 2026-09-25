#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Animation.h"
#include "Player.h"
using namespace std;
using namespace sf;


class GI {
    int maxHp;
    int Hp;

    vector<Sprite> healthSprite;
    vector<Animation*> healthAnimation;

    Image hImage;
    Texture hTextureF, hTextureE;

    Texture soul_filler_t, soul_frame_t;
    Sprite soul_filler, soul_frame;

    sf::IntRect rec;

public:

    GI(Vector2f Position, float HpDif, int Hp, int maxHp);

    //установить хп
    void setHp(int Hp_);

    //рисование
    void draw(RenderWindow& window, const View view, Vector2f winSize_);

    //обновление
    void update(float time, int HP_, int MaxHp_, int soul, int soulmax);
};


