#include "npc.h"

NPC::NPC(float X, float Y, float size, float speed)
: NPCPosX(X), NPCPosY(Y), NPCSize(size), NPCSpeed(speed) {}

//NPC are moving to the right for now
void NPC::updateNPC(){
    NPCPosX += NPCSpeed;
    //if NPC moves outside of range gets moved to other side
    if (NPCPosX > 400.0f){
        NPCPosX = -400.0f;
    }
}

float NPC::getPosX(){
    return NPCPosX;
}

float NPC::getPosY(){
    return NPCPosY;
}

float NPC::getSize(){
    return NPCSize;
}

float NPC::getSpeed(){
    return NPCSpeed;
}

void NPC::setNPCX(float X){
    NPCPosX = X;
}

void NPC::setNPCY(float Y){
    NPCPosY = Y;
}

void Sun::updateNPC(){
    setNPCY(getPosY() + getSpeed());
    if (getPosY() > 400.0f){
        setNPCY(-400.0f);
    }
}