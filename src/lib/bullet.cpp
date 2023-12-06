#include "bullet.h"
#include "borders.h"

Bullet::Bullet(float X, float Y, float bulletSpeed, float dirX, float dirY)
    : posX(X), posY(Y), speed(bulletSpeed), directionX(dirX), directionY(dirY) {}

void Bullet::updateBullet() {
    posX += speed * directionX;
    posY += speed * directionY;

    // Check if the bullet is out of bounds, and if so, mark it for removal
    if (posY > borderTop || posY < borderBottom || posX < borderLeft || posX > borderRight) {
        markForRemoval = true;
    }
}

void Bullet::drawBullet() {
    const float bulletSize = 8.0f;
    glColor3f(1.0f, 0.0f, 0.0f);  // Red 
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

bool Bullet::isMarkedForRemoval() const {
    return markForRemoval;
}
