#ifndef BULLET_H
#define BULLET_H

class Bullet {
private:
    float posX;
    float posY;
    float speed;
    float directionX;
    float directionY;
    float bulletSize = 8.0f;
    bool markedForRemoval = false;
    //used when bullets are drawn to match their colors to respective shooter
    float colorRed;
    float colorGreen;
    float colorBlue;
public:
    Bullet(float X, float Y, float bulletSpeed, float dirX, float dirY, float Red, float Green, float Blue);
    void updateBullet();
    void drawBullet();
    void markForRemoval();
    float getPosX();
    float getPosY();
    float getSize();
    bool getMarkedForRemoval() const;
};

#endif
