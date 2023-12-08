#include "player.h"
#include "borders.h"
#include <cstring>
#include <cmath>
#include <algorithm>

Player::Player() {
    //set all keyStates to 0
    memset(keyStates, 0, sizeof(keyStates));

    posX = 0.0f;
    posY = 0.0f;
    size = 30.0f;
    speed = 3.0f;
}

// Player movement
void Player::updatePlayer() {
    if (keyStates['w'] && posY < borderTop - size / 2) 
        posY += speed;
    if (keyStates['s'] && posY > borderBottom + size / 2) 
        posY -= speed;
    if (keyStates['a'] && posX > borderLeft + size / 2) 
        posX -= speed;
    if (keyStates['d'] && posX < borderRight - size / 2) 
        posX += speed;
}

// Update movement keystates
void Player::updateKey(unsigned char key, bool value) {
    keyStates[key] = value;
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

void Player::shootBullet(int mouseX, int mouseY) {
    const float BULLET_SPEED = 8.0f;  // Adjust the speed as needed

    // Calculate the direction from player to the cursor (normalized)
    float directionX = static_cast<float>(mouseX - posX);
    float directionY = static_cast<float>(mouseY - posY);
    float length = std::sqrt(directionX * directionX + directionY * directionY);

    if (length != 0) {
        directionX /= length;
        directionY /= length;

        // Create a bullet and add it to the bullets vector
        bullets.push_back(Bullet(posX, posY, BULLET_SPEED, directionX, directionY, 1.0f, 0.0f, 0.0f)); //red bullets
    }
}

std::vector<Bullet>& Player::getBullets() {
    return bullets;
}

void Player::removeMarkedBullets() {
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &b) { return b.getMarkedForRemoval(); }), bullets.end());
}

float Player::getPosX(){
    return posX;
}

float Player::getPosY(){
    return posY;
}

bool Player::checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const{
    return (std::abs(bulletX - posX) < (size / 2 + bulletSize / 2)) &&
           (std::abs(bulletY - posY) < (size / 2 + bulletSize / 2));
}