#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "text.h"
using namespace std;
using namespace sf;


//кнопка
class Button :public text {
private:

    float w, h; //ширина и высота кнопки

    SoundBuffer buffer;

    Sound sound;   //звук

    bool press;   //

public:
    RectangleShape button;//сам крвадра

    Button();

    Button(float W, float H, string strName);

    //кнопка следит за спрайтом
    void sleditForSprite(Sprite& s, float x, float y);

    //рисуеи и кнопк(квадрат) и текст
    void draw(RenderWindow& window);

    //нажатие
    bool pressed(Event& event, Vector2f  pos);

    //наведина мышка
    bool navediaMouse(Event& event, Vector2f  pos);

    //дать звук
    void getSound(string fileAudio);

    //играть звук
    void soundPlay();

    //поменять громкость
    void soundSetVolume(int volume);

    //поменять размеры квадрата кнопки
    void setButtonSize(float W, float H);

    //Поменять на центр
    void setOriginCenter();

    //поменять позицию
    void setPosition(float x, float y);

    //поменять цвет квадрата
    void setFillRacktengelColor(float R, float G, float B);
};