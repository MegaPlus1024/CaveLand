#include "Overworld.h"

Vector2f roundd(Vector2f ff) {
    return {round(ff.x), round(ff.y)};
}

void Overworld::overworld_definition() {
    fs::create_directory("alive");
    fireballcd = 400.0f;
    fireballtime = 0.0f;
    slashcd = 400.0f;
    slashtime = 0.0f;
    slashaframe = 200.0f;

    soul = 400.0f;
    soulmax = 400.0f;

    //
    player = new Player({0, 0}, {100, 200}, 1.2, 1200, 5, 5, "cloak.png"); //позиция размер офсет хп мхп картинка

    fireball_ = new Projectile({0, 0}, {500.0f, 500.0f}, {5, 0}, 5, 4000.0f, {8, 1}, "fireball.png");
    fireball.resize(20);
    for (auto& i : fireball) {
        i = new Projectile({0, 0}, {500.0f, 500.0f}, {5, 0}, 5, 4000.0f, {8, 1}, "fireball.png");
        i->active = false;
    }

    slash = new Slash(player->getPositionLink(), {520.0f, 390.0f}, {1, 0}, 2, 200.0f, {6, 2}, "slash.png");
    slash->active = false;

    //player->setOriginCenter();

    gi = new GI({0, 0}, 300.0f, player->getHp(), player->getMaxHp());

    //loadLevel("level/level1.txt");
    level = nullptr;

    theme.play();

    loadLevel("level1");
}

Overworld::Overworld() {
    //overworld_definition();
    theme.openFromFile("sound/cave_theme.ogg");
    fireballSound.openFromFile("sound/fireball.ogg");
}

Overworld::~Overworld() {
//    if (theme.getDuration().asMilliseconds() != 0) {
//        theme.stop();
//    }
    delete fireball_;
    for (auto& i : fireball) {
        delete i;
    }
    delete level;
    delete gi;
    delete player;
}

Overworld::Overworld(string *state_) {
    //overworld_definition();
    theme.openFromFile("sound/cave_theme.ogg");
    fireballSound.openFromFile("sound/fireball.ogg");
    state = state_;
}

void Overworld::loadLevel(string path) {
    if (level) {
        ofstream outdata;
        outdata.open("alive/" + level->path + ".txt");

        int a;
        for (auto& i : enemy) {
            outdata << i->isAlive << '\n';
        }
        outdata.close();

        delete level;
    }

    level = new Level(path);

    enemy = level->enemy;
    platform = level->platform;
    border = level->border;
    transition = level->transition;
    finish = level->finish;

    player->setPosition(level->startPos);
    setBackground(level->backgroundpath);
}

void Overworld::setBackground(string path) {
    mImage = Image();
    mImage.loadFromFile(path);
    mTexture = Texture();
    mTexture.loadFromImage(mImage);
    mSprite = Sprite();
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x / 2.0f,
                      mTexture.getSize().y / 2.0f);

    int mix = -2, mx = 3;
    if (path == "image/tralala.png") {
        mx = 10;
        mix = -10;
        mSprite.setScale(4, 4);
    }else {
        mix = -2;
        mx = 3;
        mSprite.setScale(6, 6);
    }
    background.clear();
    background.resize(mx - mix, vector<Sprite>(mx - mix));
    for (int i = mix; i < mx; i++) {
        for (int j = mix; j < mx; j++) {
            background[i - mix][j - mix] = mSprite;
            background[i - mix][j - mix].setPosition(i * mSprite.getGlobalBounds().width,
                                                 j * mSprite.getGlobalBounds().height);
        }
    }
}

void Overworld::keyboardLogic(float time) {
    if (isHealing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dsoul += time * soulSpeed;
            while (dsoul >= 0 && soulneed) {
                soulneed--;
                soul--;
                dsoul--;
            }
            if (soulneed < 0.00001) {
                soulneed = soulh;
                player->increaseHp(1);
                player->healSound.play();
            }
        }else {
            soul += soulh - soulneed;
            soulneed = soulh;
            dsoul = 0;
            isHealing = false;
            timerFire = 0;
        }
    }else if (isFireballing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            timerFire += time;
            if (3 * fireballcd <= timerFire) {
                isHealing = true;
                isFireballing = false;
            }
        }else {
            fireballSound.play();
            soul -= soulh;
            doFireball = true;
            isFireballing = false;
            timerFire = 0;
        }
    }else {
        if (soul >= soulh) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                timerFire += time;
                isFireballing = true;
            }
            else {
                timerFire = 0;
            }
        }
    }


    if (timerSlash == 0.0f) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            timerSlash += time;
            doSlash = true;
        }
    }else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        timerSlash = 0.0f;
    }
}

void Overworld::ProjectileUpdate(float time) {
    fireballtime -= time;
    fireballtime = max(0.0f, fireballtime);

    int cnt = 0;
    for (auto& i : fireball) {
        if (!i->active && doFireball && fireballtime == 0.0f) {
            doFireball = false;

            for (auto& j : enemy) {
                j->hitFireball[cnt] = false;
            }

            i->resetAnimation();
            fireballtime = fireballcd;
            i->setPosition(player->getPosition());
            i->active = true;
            i->aFrame = fireball_->aFrame;
            if (!player->faceRight) {
                i->velocity.x = -abs(i->velocity.x);
            }
            else {
                i->velocity.x = abs(i->velocity.x);
            }

            player->setKnockback(player->faceRight);
            break;
        }
        cnt++;
    }

    for (auto& i : fireball) {
        if (i->active) {
            i->update(time);
        }
    }






    slashtime -= time;
    slashtime = max(0.0f, slashtime);
    if (!slash->active && doSlash && slashtime == 0.0f) {
        doSlash = false;

        for (auto& i : enemy) {
            i->hitSlash = false;
        }

        slash->resetAnimation();
        slash->slash_sound.play();
        slashtime = slashcd;
        slash->active = true;
        slash->aFrame = slashaframe;
        if (!player->faceRight) {
            slash->velocity.x = -abs(slash->velocity.x);
        }
        else {
            slash->velocity.x = abs(slash->velocity.x);
        }
    }

    if (slash->active) {
        slash->update(time);
    }
}

void Overworld::CollisionUpdate(float time) {
    Vector2f direction;
    for (auto& i : enemy) {
        for (auto& j : enemy) {
            if (i != j) {
                if (j->isAlive && i->isAlive) {
                    if (i->CheckCollision(j->collider, direction, 0.5f)) {
                        i->OnCollision(direction);
                        j->OnCollision(-direction);
                    }
                }
            }
        }
    }

    for (auto& i : enemy) {
        if (i->isAlive && player->CheckCollision(i->collider, direction)) {
            player->OnEnemyCollision(time, direction, i);
        }
    }

    for (auto& i : platform) {
        if (player->CheckCollision(i->collider, direction, 0.0f)) {
            player->OnCollision(direction);
        }
    }

    for (auto& i : enemy) {
        for (auto& j : platform) {
            if (i->CheckCollision(j->collider, direction, 0.0f)) {
                i->OnCollision(direction);
            }
        }
    }
    for (auto& i : enemy) {
        int cnt = 0;
        for (auto& j : fireball) {
            if (i->isAlive && j->active && j->CheckCollision(i->collider, direction)
                && !i->hitFireball[cnt]) {
                i->hitFireball[cnt] = true;
                i->burnt.play();
                j->OnEnemyCollision(time, direction, i);

                i->setKnockback(j->faceRight, 1.5);
            }
            cnt++;
        }
    }

    for (auto& i : enemy) {
        if (i->isAlive && slash->active && slash->CheckCollision(i->collider, direction) && !i->hitSlash) {
            i->hitSlash = true;
            i->impact_sound.play();
            slash->OnEnemyCollision(time, direction, i);

            soul += soulsteel;
            soul = min(soul, soulmax);

            player->setKnockback(slash->faceRight);
            i->setKnockback(slash->faceRight, 1.5);
        }
    }

    for (auto& i : transition) {
        if (player->CheckCollision(i->collider, direction)) {
            cout << i->nextlevel << '\n';
            //cout << player->getPosition() << '\n';
            Vector2f poss = i->positionStart;
            //cout << player->getPosition() << '\n';
            loadLevel(i->nextlevel);//i->nextlevel
            player->setPosition(poss);
            player->velocity = {0.0f, 0.0f};
            return;
        }
    }

    for (auto& i : finish) {
        if (player->CheckCollision(i->collider, direction)) {
            *state = "FINISH";
            break;
        }
    }
}

void Overworld::Parallax(Vector2f velocity_) {
    for (auto& i : background) {
        for (auto& j : i) {
            j.move(velocity_ / 1.5f);
        }
    }
}

void Overworld::roundupdate() {
    /*for (auto& i : enemy) {
        auto g = roundd(i->getPosition());
        i->setPosition(g.x, g.y);
    }*/
    for (auto& i : platform) {
        auto g = roundd(i->getPosition());
        i->setPosition(g.x, g.y);
    }
    auto g = roundd(player->getPosition());
    player->setPosition(g);


}

void Overworld::update(Event event, RenderWindow &window, View& view, float time) {
    player->update(time);
    for (auto& i : enemy) {
        i->update(time, player);
    }
    CollisionUpdate(time);

    keyboardLogic(time);
    ProjectileUpdate(time);

    gi->update(time, player->getHp(), player->getMaxHp(), soul, soulmax);
    player->updateAnimation(time);

    roundupdate();

    view.setSize(winSize_.x, winSize_.y);
    Vector2f viewpos = player->getPosition();

    viewpos.x = min(border.getPosition().x + border.getSize().x / 2.0f - view.getSize().x / 2.0f, viewpos.x);
    viewpos.x = max(border.getPosition().x - border.getSize().x / 2.0f + view.getSize().x / 2.0f, viewpos.x);
    if (border.getSize().x < view.getSize().x) {
        viewpos.x = border.getPosition().x;
    }

    viewpos.y = min(border.getPosition().y + border.getSize().y / 2.0f - view.getSize().y / 2.0f, viewpos.y);
    viewpos.y = max(border.getPosition().y - border.getSize().y / 2.0f + view.getSize().y / 2.0f, viewpos.y);
    if (border.getSize().y < view.getSize().y) {
        viewpos.y = border.getPosition().y;
    }
    Parallax(viewpos - window.getView().getCenter());

    view.setCenter(viewpos);

    //view.setCenter(platform1->getPosition());
    //view.setSize(window.getSize().x * 5, window.getSize().y * 5);
    window.setView(view);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        *state = "PAUSE_MENU";
    }

    if (player->getHp() > 0) {
#ifdef godmode
        window.setTitle("HP: " + to_string(player->getHp()) + "   SOUL: " + to_string(soul)
                        + "    healing: " + to_string(isHealing) + "    fireball: " + to_string(isFireballing) +
                        "     soulneed: " + to_string(soulneed) + "            coords: "
                        + to_string(player->getPosition().x) + " " + to_string(player->getPosition().y) +
                        + "        canJump: " + to_string(player->canJump));
#else
        window.setTitle("CAVELAND");
#endif
    }else {
        *state = "GAMEOVER";
    }
}

void Overworld::draw(RenderWindow& window) {
    for (auto& i : background) {
        for (auto& j : i) {
            window.draw(j);
        }
    }

    for (auto& i : fireball) {
        if (i->active) {
            i->draw(window);
        }
    }

    player->draw(window);
    for (auto& i : enemy) {
        i->draw(window);
    }
    for (auto& i : platform) {
        i->draw(window);
    }
    for (auto& i : transition) {
        i->draw(window);
    }
    for (auto& i : finish) {
        i->draw(window);
    }
    slash->draw(window);
    gi->draw(window, window.getView(), winSize_);

}