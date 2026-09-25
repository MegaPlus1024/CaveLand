#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(int row, float deltaTime, bool faceRight) {
    currentImage.y = row;
    totalTime += deltaTime;

    while (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
    }
    while (currentImage.x >= imageCount.x) {
        currentImage.x -= imageCount.x;
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight) {
        uvRect.left = (currentImage.x) * abs(uvRect.width);
        uvRect.width = abs(uvRect.width);
    }else {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    //cout << row << '\n';
    //cout << currentImage.x << '\n';
    //cout << uvRect.left << ' ' << uvRect.width << ' ' << uvRect.top << ' ' << uvRect.height << endl;
}

void Animation::update(int row, float deltaTime, bool faceRight, pair<int, int> start) {
    currentImage.y = row;
    totalTime += deltaTime;
    imageCount.x = start.second;

    while (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
    }
    while (currentImage.x >= imageCount.x) {
        currentImage.x -= imageCount.x;
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight) {
        uvRect.left = (start.first + currentImage.x) * abs(uvRect.width);
        uvRect.width = abs(uvRect.width);
    }else {
        uvRect.left = (start.first + currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
//    cout << row << '\n';
//    cout << continue_.first << ' ' << continue_.second << '\n';
//    cout << currentImage.x << '\n';
//    cout << uvRect.left << ' ' << uvRect.width << ' ' << uvRect.top << ' ' << uvRect.height << endl;
}

void Animation::reset() {
    currentImage.x = 0;
    totalTime = 0;
}