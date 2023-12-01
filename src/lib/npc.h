#ifndef NPC_H
#define NPC_H

#include <string>

class NPC{
    private:
        float NPCPosX;
        float NPCPosY;
        float NPCSize;
        float NPCSpeed;
        float colorRed;
        float colorGreen;
        float colorBlue;

    public:
        NPC(float X, float Y, float size, float speed);
        void updateNPC();
        float getPosX();
        float getPosY();
        float getSize();
        float getSpeed();
        void setNPCX(float X);
        void setNPCY(float Y);
        float getColorRed();
        float getColorGreen();
        float getColorBlue();
};

class Sun : public NPC{
    private:
        float NPCSize = 20.0f;
        float NPCSpeed = 10.f;
        //Yellow
        colorRed = 1.0f;
        colorGreen = 1.0f;
        colorBlue = 0.0f;

    public:
        void updateNPC();
};

class Ghost : public NPC{
    private:
        float NPCSize = 15.0f;
        float NPCSpeed = 15.f;
        //White
        colorRed = 0.0f;
        colorGreen = 0.0f;
        colorBlue = 0.0f;

    public:
        void updateNPC();
};

#endif