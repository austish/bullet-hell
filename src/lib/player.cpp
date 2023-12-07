// player.cpp
#include "player.h"
#include "borders.h"
#include <cstring>
#include <cmath>

Player::Player() {
    //set all keyStates to 0
    memset(keyStates, 0, sizeof(keyStates));

    posX = 0.0f;
    posY = 0.0f;
    size = 30.0f;
    speed = 3.0f;
    score = 0;
    health = 0;
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


float Player::getX() const {
    return posX;
}

float Player::getY() const {
    return posY;
}

float Player::getSize() const {
    return size;
}
