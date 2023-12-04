#ifndef NPC_H
#define NPC_H
#include <string>

class NPC{
    private:
        float posX;
        float posY;
        float size;
        float speed;
        int state; // 1 for alive, 0 for dead
    public:
        NPC(float X, float Y, float size, float speed);
        void updateNPC();
        void drawNPC();
};

#endif