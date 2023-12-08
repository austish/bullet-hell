// NPC Class
#ifndef NPC_H
#define NPC_H
#include <string>
#include <vector>
#include "bullet.h"
#include <algorithm>
#include <cmath>

enum ShapeType { SQUARE, TRIANGLE, CIRCLE };
enum NPCState { NORMAL, EVASIVE }; // State of the NPC

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
        NPCState state; // Updated to use NPCState enum
        ShapeType shape; // Shape of the NPC
        NPC(float X, float Y, float size, float speed, ShapeType shapeType); 
        void updateNPC(float playerPosX, float playerPosY); // Updated to take player's position
        // Method for collision detection
        bool checkCollisionWithPlayer(float playerX, float playerY, float playerSize) const;
        void removeMarkedBullets();
};

#endif
