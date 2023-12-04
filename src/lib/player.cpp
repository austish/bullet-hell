#include "player.h"
#include "borders.h"
#include <cstring>

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

//Draw player (red)
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