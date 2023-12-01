#ifndef NPC_H
#define NPC_H

#include <string>

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
        float getSpeed();
        void setNPCX(float X);
        void setNPCY(float Y);
};

class Sun : public NPC{
    private:
        float NPCSize = 20.0f;
        float NPCSpeed = 10.f;
        //used to make different kinds of NPC different colors in main
        string color = "Yellow";
    public:
        void updateNPC();
};

class Ghost : public NPC{
    private:
        float NPCSize = 15.0f;
        float NPCSpeed = 15.f;
        //used to make different kinds of NPC different colors in main
        string color = "White";
    public:
        void updateNPC();
};

#endif