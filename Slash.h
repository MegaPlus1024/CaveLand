#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Animation.h"
#include "Collider.h"
#include <fstream>
using namespace std;
using namespace sf;

class Bat;
class Turtle;
class Hopper;
class Entity;

class Slash {
private:

    Vector2u mImageCount;
    int row;
    Animation* animation;


    Vector2f* playerPosition;
    Vector2f mPosition;
    Vector2f mSize;
    float speed;
    float accel;

    Image mImage;
    Texture mTexture;

public:
    Music slash_sound;
    bool faceRight;

    bool active;

    float aFrame;

    RectangleShape* body;
    Collider* collider;

    Vector2f velocity;
    Vector2f acceleration;

    int damage;

    Vector2f spritePos;
    Vector2f spriteSize;
    Sprite mSprite; //сам игрок

    Slash(Vector2f* Position, Vector2f size, Vector2f velocity_, int damage, float time_, Vector2u ImageCount, const string image);

    //рисует героя
    void draw(RenderWindow& window);

    //поменять размеры квадрата кнопки
    void setSize(float W, float H);
/*
    //Поменять на центр
    void setOriginCenter();*/

    void setSpriteBody(Vector2f spritePos_, Vector2f spriteSize_);

    //Поменять на центр
    void setOriginCenter();

    //обновление движения
    void updateMove(float time);

    void resetAnimation();

    //получить позицию
    Vector2f getPosition();

    //проверка колизий
    bool CheckCollision(Collider *other, sf::Vector2f& direction);

    //обработка коллизий
    void OnCollision(sf::Vector2f direction);

    void OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy);

    void timerUpdate(float time);

    //обновление
    void updateAnimation(float time);

    void updateSound();

    //обновление
    void update(float time);
};