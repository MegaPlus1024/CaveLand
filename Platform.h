#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Geometry.h"
#include "Animation.h"
#include "Collider.h"
using namespace std;
using namespace sf;

class Player;

class Platform {
private:
    bool active;

    SoundBuffer buffer;

    Sound stepsSound;   //звук шагов

    Vector2f mPosition;
    Vector2f mSize;

    Image mImage;
    Texture mTexture;

public:
    RectangleShape* body;
    Collider* collider;

    Sprite mSprite; //сам игрок

    Platform(Vector2f Position, Vector2f size);

    Platform(Vector2f Position, Vector2f size, string path_);

    //рисует героя
    void draw(RenderWindow& window);

    //дать звук
    void getSound(string failAudio);

    //поменять громкость
    void soundSetVolume(int volume);

    //поменять размеры квадрата кнопки
    void setSize(float W, float H);
/*
    //Поменять на центр
    void setOriginCenter();*/

    //поменять позицию
    void setPosition(float x, float y);

    //получить позицию
    Vector2f getPosition();

    //проверка колизий
    bool CheckCollision(Collider *other, sf::Vector2f& direction, float push);

    //обработка коллизий
    void OnCollision(sf::Vector2f direction);

    void setTexture(string path_);
};