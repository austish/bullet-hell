#include "player.h"
#include <cstring>
#include <cmath>
#include <algorithm>

Player::Player() {
    //set all keyStates to 0
    memset(keyStates, 0, sizeof(keyStates));

<<<<<<< Updated upstream
    playerPosX = 0.0f;
    playerPosY = 0.0f;
    playerSize = 40.0f;
    playerSpeed = 5.0f;
=======
    posX = 0.0f;
    posY = 0.0f;
    size = 30.0f;
    speed = 3.0f;
    bulletSpeed = 5.0f;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
}

//Draw player
void Player::drawPlayer() {
   glColor3f(1.0f, 0.0f, 0.0f);                       // Set color to red
   glPushMatrix();                                    // Push player matrix
   glTranslatef(posX, posY, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-size / 2, -size / 2);
   glVertex2f(size / 2, -size / 2);
   glVertex2f(size / 2, size / 2);
   glVertex2f(-size / 2, size / 2);
   glEnd();
   glPopMatrix();                                    // Pop player matrix
}

void Player::shootBullet(float mouseX, float mouseY) {
    float directionX = mouseX - posX;
    float directionY = mouseY - posY;
    float magnitude = sqrt(directionX * directionX + directionY * directionY);

    if (magnitude != 0) {
        directionX /= magnitude;
        directionY /= magnitude;

        Bullet newBullet(posX, posY, bulletSpeed, directionX, directionY);
        bullets.push_back(newBullet);
    }
}


std::vector<Bullet>& Player::getBullets() {
    return bullets;
}

void Player::removeMarkedBullets() {
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &b) { return b.isMarkedForRemoval(); }), bullets.end());
}

float Player::getPosX(){
    return posX;
}

float Player::getPosY(){
    return posY;
>>>>>>> Stashed changes
}