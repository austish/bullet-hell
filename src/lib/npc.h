#ifndef NPC_H
#define NPC_H
#include <string>
#include <vector>
#include "bullet.h"

class NPC{
    private:
        float posX;
        float posY;
        float size;
        float speed;
        bool markedForRemoval = false;
        double lastShotTime;
        double shootingInterval = 3000; // Time interval between shots 3 seconds
        std::vector<Bullet> bullets;
    public:
        NPC(float X, float Y, float size, float speed);
        std::vector<Bullet>& getBullets();
        void updateNPC();
        void drawNPC();
        void shootBullets();
        bool checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const;
        void markForRemoval();
        bool getMarkedForRemoval() const;
};

#endif