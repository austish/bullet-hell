#include "npc.h"
#include "borders.h"

NPC::NPC(float X, float Y, float size, float speed)
: posX(X), posY(Y), size(size), speed(speed) {}

//NPC are moving to the right for now
void NPC::updateNPC(){
    posX += speed;
    //if NPC moves outside of range gets moved to other side
    if (posX > borderRight - size / 2){
        posX = -400.0f;
    }
}

void NPC::drawNPC(){
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-size / 2, -size / 2);
    glVertex2f(size / 2, -size / 2);
    glVertex2f(size / 2, size / 2);
    glVertex2f(-size / 2, size / 2);
    glEnd();
    glPopMatrix();
}
