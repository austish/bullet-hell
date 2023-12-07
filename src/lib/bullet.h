#ifndef BULLET_H
#define BULLET_H

class Bullet {
private:
    float posX;
    float posY;
    float speed;
    float directionX;
    float directionY;
    bool markForRemoval = false;
    //used when bullets are drawn to match their colors to respective shooter
    float colorRed;
    float colorGreen;
    float colorBlue;
public:
    Bullet(float X, float Y, float bulletSpeed, float dirX, float dirY, float Red, float Green, float Blue);
    void updateBullet();
    void drawBullet();
    bool isMarkedForRemoval() const;
};

#endif
