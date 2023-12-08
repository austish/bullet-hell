#ifndef NPC_H
#define NPC_H

#include "bullet.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

enum ShapeType { SQUARE, TRIANGLE, CIRCLE };
enum NPCState { NORMAL, EVASIVE };

class NPC{
    private:
        float posX;
        float posY;
        float size;
        float speed;
        bool markedForRemoval = false;
        double lastShotTime;
        double shootingInterval = 3000; // Time interval between shots of 3 seconds
        std::vector<Bullet> bullets;
        NPCState state; // Updated to use NPCState enum
        ShapeType shape; // Shape of the NPC
    public:
        NPC(float X, float Y, float size, float speed, ShapeType shapeType); 
        void updateNPC(float playerPosX, float playerPosY); 
        void drawNPC();
        void shootBullets();
        void markForRemoval();
        void removeMarkedBullets();
        bool getMarkedForRemoval() const;
        std::vector<Bullet>& getBullets();
        bool checkCollisionWithPlayer(float playerX, float playerY, float playerSize) const;
        bool checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const;
        
};

#endif
