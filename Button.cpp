#include "Button.h"

Button::Button() {

}

Button::Button(float W, float H, string strName) : text(strName) {
    w = W;
    h = H;

    press = false;

    button.setSize(Vector2f(W, H));

    txt.setPosition(button.getPosition());
}

//кнопка следит за спрайтом
void Button::sleditForSprite(Sprite &s, float x, float y) {

    button.setPosition(s.getPosition().x + x, s.getPosition().y + y);
    txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
}

//рисует и кнопку(квадрат) и текст
void Button::draw(RenderWindow &window) {
    txt.setPosition(button.getPosition() - Vector2f(0.0f, 90.0f));

    window.draw(button);
    window.draw(txt);
}

//нажатие
bool Button::pressed(Event &event, Vector2f pos) {
    if (button.getGlobalBounds().contains(pos.x, pos.y) && event.type == Event::MouseButtonPressed && !press) {
        if (event.key.code == Mouse::Left) {
            press = true;
            return true;
        }
    }


    if (!(press)) return false;

    else { //press

        if (!(event.type == Event::MouseButtonPressed)) {
            press = false;
        }

        return false;
    }
};

//наведина мышка
bool Button::navediaMouse(Event &event, Vector2f pos) {
    if (button.getGlobalBounds().contains(pos.x, pos.y)) return true;

    else return false;
}

//дать звук
void Button::getSound(string fileAudio) {
    buffer.loadFromFile(fileAudio);

    sound.setBuffer(buffer);
}

//играть звук
void Button::soundPlay() {
    sound.play();
}

//поменять громкость
void Button::soundSetVolume(int volume) {
    sound.setVolume(volume);
}

//поменять размеры квадрата кнопки
void Button::setButtonSize(float W, float H) {
    w = W;
    h = H;

    button.setSize(Vector2f(W, H));
}

//Поменять на центр
void Button::setOriginCenter() {
    button.setOrigin(w / 2, h / 2);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
}

//поменять позицию
void Button::setPosition(float x, float y) {
    button.setPosition(x, y);
}

//поменять цвет квадрата
void Button::setFillRacktengelColor(float R, float G, float B) {
    button.setFillColor(Color(R, G, B));
}