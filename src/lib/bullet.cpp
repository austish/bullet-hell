#include "bullet.h"
#include "borders.h"

Bullet::Bullet(float X, float Y, float bulletSpeed, float dirX, float dirY, float Red, float Green, float Blue)
    : posX(X), posY(Y), speed(bulletSpeed), directionX(dirX), directionY(dirY), colorRed(Red), colorGreen(Green), colorBlue(Blue) {}

void Bullet::updateBullet() {
    posX += speed * directionX;
    posY += speed * directionY;

    // Check if the bullet is out of bounds,if it is mark it for removal
    if (posY > borderTop || posY < borderBottom || posX < borderLeft || posX > borderRight) {
        markedForRemoval = true;
    }
}

void Bullet::drawBullet() {
    glColor3f(colorRed, colorGreen, colorBlue);  // Color should match respective player/NPC
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-bulletSize / 2, -bulletSize / 2);
    glVertex2f(bulletSize / 2, -bulletSize / 2);
    glVertex2f(bulletSize / 2, bulletSize / 2);
    glVertex2f(-bulletSize / 2, bulletSize / 2);
    glEnd();
    glPopMatrix();
}

void Bullet::markForRemoval(){
    markedForRemoval = true;
}

float Bullet::getPosX(){
    return posX;
}

float Bullet::getPosY(){
    return posY;
}

float Bullet::getSize(){
    return bulletSize;
}

bool Bullet::getMarkedForRemoval() const {
    return markedForRemoval;
}