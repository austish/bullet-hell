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

// Player movement
void Player::updatePlayer() {
    if (keyStates['w'] && playerPosY < borderTop - playerSize / 2) 
        playerPosY += playerSpeed;
    if (keyStates['s'] && playerPosY > borderBottom + playerSize / 2) 
        playerPosY -= playerSpeed;
    if (keyStates['a'] && playerPosX > borderLeft + playerSize / 2) 
        playerPosX -= playerSpeed;
    if (keyStates['d'] && playerPosX < borderRight - playerSize / 2) 
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

// Update movement keystates
void Player::updateKey(unsigned char key, bool value) {
    keyStates[key] = value;
}

//Draw player (red)
void Player::drawPlayer() {
   glColor3f(1.0f, 0.0f, 0.0f);                       // Set color to red
   glPushMatrix();                                    // Push player matrix
   glTranslatef(playerPosX, playerPosY, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, playerSize / 2);
   glVertex2f(-playerSize / 2, playerSize / 2);
   glEnd();
   glPopMatrix();                                    // Pop player matrix
}