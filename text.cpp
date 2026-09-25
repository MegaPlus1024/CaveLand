#include "text.h"

text::text() {

}

text::text(string strName) {
    //font.loadFromFile("font/Jost/Jost-Italic-VariableFont_wght.ttf");
    font.loadFromFile("font/Overpass/Overpass-Italic-VariableFont_wght.ttf");

    txt.setFont(font);
    txt.setCharacterSize(20);

    //начальный цвет
    txt.setFillColor(Color(0, 0, 0));

    txt.setString(strName);

    str = strName;
}

//текст будет следить за спрайтом
void text::sleditForSprite(Sprite &s, float x, float y) {
    txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
}

//дать число тексту
void text::getChislo(float n) {
    ostringstream chislo;

    chislo << n;

    txt.setString(str + chislo.str());
}

//ф-я для текста
void text::setString(string name) {
    txt.setString(name);
}

void text::setPosition(float x, float y) {
    txt.setPosition(x, y);
}

void text::setPosition(Vector2f pos) {
    txt.setPosition(pos);
}

//Поменять на центр
void text::setOriginCenter() {
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
}

void text::setFillTextColor(float R, float G1, float B) {
    txt.setFillColor(Color(R, G1, B));
}
//

//поменять размер шрифта
void text::setCharacterSize(float a) {
    txt.setCharacterSize(a);
}

//нарисовать в окне
void text::draw(RenderWindow &window) {
    window.draw(txt);
}

