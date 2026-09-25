#include "GI.h"

GI::GI(Vector2f Position, float HpDif, int Hp, int maxHp) {
    hImage.loadFromFile("image/heartF.png");
    hTextureF.loadFromImage(hImage);
    hImage.loadFromFile("image/heartE.png");
    hTextureE.loadFromImage(hImage);
    healthSprite.resize(maxHp);

    for (auto& i : healthSprite) {
        i.setTexture(hTextureF);
    }

//    for (auto& i : healthAnimation) {
//        i = new Animation(hTexture, {?, ?}, 120.0f);
//    }

    for (int i = 0; i < maxHp; i++) {
        healthSprite[i].setPosition(Position.x + i * HpDif, Position.y);
    }


    hImage.loadFromFile("image/soul_frame2.png");
    soul_frame_t.loadFromImage(hImage);
    soul_frame.setTexture(soul_frame_t);

    hImage.loadFromFile("image/soul_filler2.png");
    soul_filler_t.loadFromImage(hImage);
    soul_filler.setTexture(soul_filler_t);

    soul_filler.setPosition(Position.x, Position.y + 400.0f);
    soul_frame.setPosition(Position.x, Position.y + 400.0f);
}

void GI::draw(RenderWindow& window, const View view, Vector2f winSize_) {
    for (auto& i : healthSprite) {
        i.setPosition(i.getPosition() + view.getCenter() - (winSize_ / 2.0f));
        window.draw(i);
        i.setPosition(i.getPosition() - view.getCenter() + (winSize_ / 2.0f));
    }


    soul_frame.setPosition(soul_frame.getPosition() + view.getCenter() - (winSize_ / 2.0f));
    window.draw(soul_frame);

    auto pos_ = soul_frame.getPosition();
    soul_filler.setPosition({pos_.x, pos_.y + rec.top});

    window.draw(soul_filler);


    soul_frame.setPosition(soul_frame.getPosition() - view.getCenter() + (winSize_ / 2.0f));
    soul_filler.setPosition({pos_.x, pos_.y + rec.top});
}

void GI::update(float time, int HP_, int MaxHp_, int soul, int soulmax) {
//    for (auto& i : healthAnimation) {
//        i->update(row, time, faceRight, col);
//    }
    for (int i = 0; i < healthSprite.size(); i++) {
        if (i < HP_) {
            healthSprite[i].setTexture(hTextureF);
        }else {
            healthSprite[i].setTexture(hTextureE);
        }
    }

    rec.width = soul_filler_t.getSize().x;
    rec.height = int(1.0f * soul_filler_t.getSize().y * soul / soulmax);
    rec.top = soul_filler_t.getSize().y - rec.height;
    soul_filler.setTextureRect(rec);
}