#include "npc.h"
#include "variables.h"

NPC::NPC(float X, float Y, float size, float speed)
: NPCPosX(X), NPCPosY(Y), NPCSize(size), NPCSpeed(speed) {}

//NPC are moving to the right for now
void NPC::updateNPC(){
    NPCPosX += NPCSpeed;
    //if NPC moves outside of range gets moved to other side
    if (NPCPosX > boundaryRight - NPCSize / 2){
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
