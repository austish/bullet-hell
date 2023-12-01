#include "npc.h"



npc::NPC(float X, float Y, float size, float speed)
: NPCPosX(X), NPCPosY(Y), NPCSize(size), NPCSpeed(speed) {}

void npc::updateNPC(){
    npcPosX += npcSpeed;
    //if NPC moves outside of range gets moved to other side
    if (npcPosX > 400.0f){
        npcPosX = -400.0f;
    }
}

float npc::getPosX(){
    return NPCPosX;
}

float npc::getPosY(){
    return NPCPosY;
}

float npc::getSize(){
    return NPCSize;
}
