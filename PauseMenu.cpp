#include "PauseMenu.h"


PauseMenu::PauseMenu(const Vector2f& winSize_) {
    winSizex = winSize_.x;
    winSizey = winSize_.y;
}

PauseMenu::PauseMenu(string* state_, const Vector2f& winSize_) {
    state = state_;
    winSizex = winSize_.x;
    winSizey = winSize_.y;
    pad = new RectangleShape();
}

//���������� ������
void PauseMenu::updateButtonStart(Event event, RenderWindow& window, View& view) {
    Vector2i mouse = Mouse::getPosition(window);
    Vector2f mousePosition = window.mapPixelToCoords(mouse);

    Vector2f filpos = view.getCenter() - view.getSize() / 2.0f + resumepos;
    resume->setPosition(filpos.x, filpos.y);

    filpos = view.getCenter() - view.getSize() / 2.0f + exitpos;
    exit->setPosition(filpos.x, filpos.y);

    pad->setPosition(view.getCenter());
    pad->setSize(view.getSize());
    pad->setOrigin(view.getSize() / 2.0f);
    pad->setFillColor(sf::Color(128,128,128, 100));

    if (resume->navediaMouse(event, mousePosition)) {
        resume->setFillRacktengelColor(100, 200, 255);
    }
    else {
        resume->setFillRacktengelColor(160, 234, 242);
    }
    if (resume->pressed(event, mousePosition)) {
        resume->soundPlay();
        PauseMenuTheme.stop();
        *state = "GAME_OVERWORLD";
    }

    if (exit->navediaMouse(event, mousePosition)) {
        exit->setFillRacktengelColor(100, 200, 255);
    }
    else {
        exit->setFillRacktengelColor(160, 234, 242);
    }
    if (exit->pressed(event, mousePosition)) {
        exit->soundPlay();
        PauseMenuTheme.stop();
        *state = "START_MENU";
    }
}


void PauseMenu::setBackground(string path_) {
//    mImage.loadFromFile(path_);
//    mTexture.loadFromImage(mImage);
//    background.setPosition(0, 0);
//    background.setTexture(mTexture);
//    background.setScale(3.0f * winSizex / mTexture.getSize().x, 3.0f * winSizey / mTexture.getSize().y);
}

void PauseMenu::update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time) {
    updateButtonStart(event, window, view);
    window.setView(view);
}

void PauseMenu::draw(RenderWindow& window) {
    window.draw(*pad);
    resume->draw(window);
    exit->draw(window);
}