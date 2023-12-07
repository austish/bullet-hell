#include "npc.h"
#include "borders.h"

NPC::NPC(float X, float Y, float size, float speed)
: posX(X), posY(Y), size(size), speed(speed) {}

std::vector<Bullet>& NPC::getBullets() {
    return bullets;
}

//NPC are moving to the right for now
void NPC::updateNPC(){
    posX += speed;
    //if NPC moves outside of range gets moved to other side
    if (posX > borderRight - size / 2){
        posX = -400.0f;
    }
}

void NPC::drawNPC(){
    glColor3f(1.0f, 1.0f, 0.0f); //yellow
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

void NPC::shootBullets() {
    const float BULLET_SPEED = 3.5f;  // Adjust the speed as needed

    // Check if enough time has passed since the last shot
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastShotTime >= shootingInterval) {
        // Reset the last shot time
        lastShotTime = currentTime;

        // Create and store 4 bullets (up, left, right, down)
        bullets.push_back(Bullet(posX, posY + BULLET_SPEED, BULLET_SPEED, 0.0f, 1.0f)); // Up
        bullets.push_back(Bullet(posX - BULLET_SPEED, posY, BULLET_SPEED, -1.0f, 0.0f)); // Left
        bullets.push_back(Bullet(posX + BULLET_SPEED, posY, BULLET_SPEED, 1.0f, 0.0f)); // Right
        bullets.push_back(Bullet(posX, posY - BULLET_SPEED, BULLET_SPEED, 0.0f, -1.0f)); // Down
    }
}