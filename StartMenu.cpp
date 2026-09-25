#include "StartMenu.h"


StartMenu::StartMenu(const Vector2f& winSize_) {
    winSizex = winSize_.x;
    winSizey = winSize_.y;
}

StartMenu::StartMenu(string* state_, const Vector2f& winSize_) {
    state = state_;
    winSizex = winSize_.x;
    winSizey = winSize_.y;
}

//обновление кнопок
void StartMenu::updateButtonStart(Event event, RenderWindow& window) {
    Vector2i mouse = Mouse::getPosition(window);
    Vector2f mousePosition = window.mapPixelToCoords(mouse);

    if (start->navediaMouse(event, mousePosition)) {
        start->setFillRacktengelColor(100, 200, 255);
    }
    else {
        start->setFillRacktengelColor(160, 234, 242);
    }
    if (start->pressed(event, mousePosition)) {
        start->soundPlay();
        startMenuTheme.stop();
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
        sleep(milliseconds(400));
        window.close();
    }
}

void StartMenu::setBackground(string path_) {
    mImage.loadFromFile(path_);
    mTexture.loadFromImage(mImage);
    background.setPosition(0, 0);
    background.setTexture(mTexture);
    background.setScale(1.0f * winSizex / mTexture.getSize().x, 1.0f * winSizey / mTexture.getSize().y);
}

void StartMenu::update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time) {
    startMenuTheme.setVolume(20);
    if (startMenuTheme.getStatus() != startMenuTheme.Playing) {
        startMenuTheme.play();
    }
    updateButtonStart(event, window);
    view.setCenter(winSize_ / 2.0f);
    view.setSize(winSize_);
    window.setView(view);
}

void StartMenu::draw(RenderWindow& window) {
    window.draw(background);
    start->draw(window);
    exit->draw(window);
}