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
        int state; // 1 for alive, 0 for dead
        double lastShotTime;
        double shootingInterval = 3000; // Time interval between shots 3 seconds
        std::vector<Bullet> bullets;
    public:
        NPC(float X, float Y, float size, float speed);
        std::vector<Bullet>& getBullets();
        void updateNPC();
        void drawNPC();
        void shootBullets();
};

#endif