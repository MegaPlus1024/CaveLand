#include "FinishMenu.h"


FinishMenu::FinishMenu(const Vector2f& winSize_) {
    winSizex = winSize_.x;
    winSizey = winSize_.y;
}

FinishMenu::FinishMenu(string* state_, const Vector2f& winSize_) {
    state = state_;
    winSizex = winSize_.x;
    winSizey = winSize_.y;
}

//обновление кнопок
void FinishMenu::updateButtonStart(Event event, RenderWindow& window) {
    Vector2i mouse = Mouse::getPosition(window);
    Vector2f mousePosition = window.mapPixelToCoords(mouse);

    if (continue_->navediaMouse(event, mousePosition)) {
        continue_->setFillRacktengelColor(100, 200, 255);
    }
    else {
        continue_->setFillRacktengelColor(160, 234, 242);
    }
    if (continue_->pressed(event, mousePosition)) {
        continue_->soundPlay();
        FinishMenuTheme.stop();
        if (*state == "FINISH") {
            int bestcur, cur;
            ifstream indata;
            indata.open("game_data/best.txt");
            indata >> bestcur;
            indata.close();
            indata.open("game_data/current.txt");
            indata >> cur;
            indata.close();
            if (bestcur < cur) {
                ofstream outdata("game_data/best.txt");
                outdata << cur << '\n';
                outdata.close();
            }
        }
        *state = "START_MENU";
    }
}

void FinishMenu::setBackground(string path_) {
    mImage.loadFromFile(path_);
    mTexture.loadFromImage(mImage);
    if (*state == "FINISH") {
        mTexture.setRepeated(true);
        background = Sprite(mTexture, IntRect(0, 0, winSizex, winSizey));
    }else {
        mTexture.setRepeated(false);
        background.setPosition(0, -500);
        background.setTexture(mTexture);
        background.setScale(1.0f * winSizex / mTexture.getSize().x, 1.0f * winSizey / mTexture.getSize().y);
    }
}

void FinishMenu::update(Event event, RenderWindow& window, View& view, const Vector2f& winSize_, float time) {
    if (*state == "FINISH") {
        int bestcur, cur;
        ifstream indata;
        indata.open("game_data/best.txt");
        indata >> bestcur;
        indata.close();
        indata.open("game_data/current.txt");
        indata >> cur;
        indata.close();
        if (bestcur < cur) {
            score->setString("NEW RECORD: " + to_string(cur));
            score->setFillTextColor(235, 38, 38);
            score->setFillRacktengelColor(252, 252, 40);
            score->setOriginCenter();
            score->setButtonSize(1500 * 3, 400 * 3);
        }else {
            score->setString("Score: " + to_string(cur));
            score->setFillTextColor(108, 187, 240);
            score->setFillRacktengelColor(167, 242, 160);
            score->setOriginCenter();
            score->setButtonSize(1000 * 3, 400 * 3);
        }
    }

    if (FinishMenuTheme.getStatus() != FinishMenuTheme.Playing) {
        FinishMenuTheme.play();
    }
    updateButtonStart(event, window);
    view.setCenter(winSize_ / 2.0f);
    view.setSize(winSize_);
    window.setView(view);
}

void FinishMenu::draw(RenderWindow& window) {
    window.draw(background);
    if (*state == "FINISH") {
        score->draw(window);
    }
    continue_->draw(window);
}