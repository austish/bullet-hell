#ifndef NPC_H
#define NPC_H

class NPC{
    private:
        float NPCPosX;
        float NPCPosY;
        float NPCSize;
        float NPCSpeed;
    public:
        NPC(float X, float Y, float size, float speed);
        void updateNPC();
        float getPosX();
        float getPosY();
        float getSize();
        void drawNPC();
};

#endif