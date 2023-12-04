#include "player.h"
#include "variables.h"
#include <cstring>

Player::Player() {
    //set all keyStates to 0
    memset(keyStates, 0, sizeof(keyStates));

    playerPosX = 0.0f;
    playerPosY = 0.0f;
    playerSize = 30.0f;
    playerSpeed = 3.0f;
}

void Player::updatePlayer() {
    if (keyStates['w'] && playerPosY < boundaryTop - playerSize / 2) 
        playerPosY += playerSpeed;
    if (keyStates['s'] && playerPosY > boundaryBottom + playerSize / 2) 
        playerPosY -= playerSpeed;
    if (keyStates['a'] && playerPosX > boundaryLeft + playerSize / 2) 
        playerPosX -= playerSpeed;
    if (keyStates['d'] && playerPosX < boundaryRight - playerSize / 2) 
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