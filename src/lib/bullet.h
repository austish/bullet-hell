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
public:
    Bullet(float X, float Y, float bulletSpeed, float dirX, float dirY);
    void updateBullet();
    void drawBullet();
    bool isMarkedForRemoval() const;
};

#endif
