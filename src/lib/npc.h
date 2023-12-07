// NPC Class
#ifndef NPC_H
#define NPC_H
#include <string>
#include <cmath>

enum ShapeType { SQUARE, TRIANGLE, CIRCLE };
enum NPCState { NORMAL, EVASIVE }; // State of the NPC

class NPC{
    private:
        float posX;
        float posY;
        float size;
        float speed;
        int state; // 1 for alive, 0 for dead
        NPCState state; // Updated to use NPCState enum
        ShapeType shape; // Shape of the NPC
    public:
        NPC(float X, float Y, float size, float speed, ShapeType shapeType); 
        void updateNPC(float playerPosX, float playerPosY); // Updated to take player's position
        void drawNPC();
        // Method for collision detection
        bool checkCollisionWithPlayer(float playerX, float playerY, float playerSize) const;
};

#endif
