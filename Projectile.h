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

class Projectile {
private:

    int row;
    Animation* animation;

    SoundBuffer buffer;

    Sound stepsSound;   //звук шагов

    Vector2f mPosition;
    Vector2f mSize;

    Vector2f spriteSize;
    float speed;
    float accel;

    Image mImage;
    Texture mTexture;

public:
    bool faceRight;

    bool active;

    float aFrame;

    RectangleShape* body;
    Collider* collider;

    Vector2f velocity;
    Vector2f acceleration;

    int damage;

    Sprite mSprite; //сам игрок

    Projectile(Vector2f Position, Vector2f size, Vector2f velocity_, int damage, float time_, Vector2u ImageCount, const string image);

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
    void setPosition(Vector2f mPosition_);

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

    void OnEnemyCollision(float time, sf::Vector2f direction, Bat* enemy);

    void OnEnemyCollision(float time, sf::Vector2f direction, Turtle* enemy);

    void OnEnemyCollision(float time, sf::Vector2f direction, Hopper* enemy);

    void OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy);

    void timerUpdate(float time);

    //обновление
    void update(float time);
};