#include "player.h"
#include <cstring>

Player::Player() {
    // set all keyStates to 0
    memset(keyStates, 0, sizeof(keyStates));

    playerPosX = 0.0f;
    playerPosY = 0.0f;
    playerSize = 40.0f;
    playerSpeed = 5.0f;
}

void Player::updatePlayer() {
    if (keyStates['w'])
        playerPosY += playerSpeed;
    if (keyStates['s'])
        playerPosY -= playerSpeed;
    if (keyStates['a'])
        playerPosX -= playerSpeed;
    if (keyStates['d'])
        playerPosX += playerSpeed;
}

float Player::getPosX() {
    return playerPosX;
}

float Player::getPosY() {
    return playerPosY;
}

float Player::getSize() {
    return playerSize;
}

void Player::updateKey(unsigned char key, bool value) {
    keyStates[key] = value;
}