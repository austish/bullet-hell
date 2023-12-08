// player.cpp
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
    score = 0;
    health = 3;
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

void Player::updateHealth(int amount) {
    health += amount;
}

void Player::updateScore(int amount) {
    score += amount;
}

int Player::getScore() {
    return score;
}

int Player::getHealth() {
    return health;
}

void Player::resetPlayer() {
    posX = 0.0f;
    posY = 0.0f;
    score = 0;
    health = 3;
}

//Draw player
void Player::drawPlayer() {
    // Body (Circle)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the devil shape
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(cos(degInRad) * (size / 2), sin(degInRad) * (size / 2));
    }
    glEnd();

    // Left Ear (Triangle)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for ears
    glBegin(GL_TRIANGLES);
    glVertex2f(-size / 4, size / 4);
    glVertex2f(-size / 4 - 10.0f, size / 4 + 15.0f);
    glVertex2f(-size / 4 - 20.0f, size / 4);
    glEnd();

    // Right Ear (Triangle)
    glBegin(GL_TRIANGLES);
    glVertex2f(size / 4, size / 4);
    glVertex2f(size / 4 + 10.0f, size / 4 + 15.0f);
    glVertex2f(size / 4 + 20.0f, size / 4);
    glEnd();

    // Tail (Line)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the tail
    glBegin(GL_LINES);
    glVertex2f(size / 4, -size / 4);
    glVertex2f(size / 4 + 20.0f, -size / 4 - 5.0f);
    glEnd();

    // Triangle at the End of the Tail
    glBegin(GL_TRIANGLES);
    glVertex2f(size / 4 + 20.0f, -size / 4 - 5.0f);
    glVertex2f(size / 4 + 20.0f, -size / 4 - 15.0f);
    glVertex2f(size / 4 + 30.0f, -size / 4 - 10.0f);
    glEnd();

    // Devilish Face (Circle)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the face
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(cos(degInRad) * (size / 8), sin(degInRad) * (size / 8) + size / 8);
    }
    glEnd();

    glPopMatrix();
}

float Player::getSize() const {
    return size;
}
