#include "npc.h"
#include "borders.h"

NPC::NPC(float X, float Y, float Size, float Speed, ShapeType Shape)
: posX(X), posY(Y), size(Size), speed(Speed), shape(Shape), state(NORMAL) {}

void NPC::updateNPC(float playerPosX, float playerPosY) {
    // Calculate distance to player
    float dx = posX - playerPosX;
    float dy = posY - playerPosY;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the player is too close to the NPC
    float evasiveThreshold = 110.0f;
    if (distance < evasiveThreshold) {
        if (posX < playerPosX) {
            posX -= speed;
        } else {
            posX += speed;
        }

        if (posY < playerPosY) {
            posY -= speed;
        } else {
            posY += speed;
        }
    } else {
        if (shape == TRIANGLE) {
            // Define a timer for direction change delay
            static int directionChangeDelay = 100; // Change direction every 500 milliseconds
            static int lastDirectionChangeTime = 0;

            // Check if it's time to change direction
            int currentTime = glutGet(GLUT_ELAPSED_TIME);
            if (currentTime - lastDirectionChangeTime > directionChangeDelay) {
                // Triangles move diagonally at an increased speed
                float diagonalSpeed = speed * 2.5f; // Increase the speed for triangles

                // Generate random directions for X and Y (-1 or 1)
                int randomDirectionX = (rand() % 2 == 0) ? -1 : 1;
                int randomDirectionY = (rand() % 2 == 0) ? -1 : 1;

                posX += diagonalSpeed * randomDirectionX;
                posY += diagonalSpeed * randomDirectionY;

                // Update the last direction change time
                lastDirectionChangeTime = currentTime;
            }
        } else {
            // Normal movement for non-triangles
            posX += speed;
        }

        // Wrap around logic
        if (posX > borderRight - size / 2) {
            posX = borderLeft + size / 2;
        } else if (posX < borderLeft + size / 2){
            posX = borderRight - size / 2;
        }
        
        if(posY > borderTop - size /2){
            posY = borderBottom + size / 2;
        } else if(posY < borderBottom + size / 2){
            posY = borderTop - size / 2;
        }
    }
}

void NPC::drawNPC(){
    glColor3f(1.0f, 1.0f, 0.0f); // Set color to yellow
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Draw the NPC shapes which can be square, circle, or triangle
    switch(shape) {
        case SQUARE:
            glBegin(GL_QUADS);
                glVertex2f(-size / 2, -size / 2);
                glVertex2f(size / 2, -size / 2);
                glVertex2f(size / 2, size / 2);
                glVertex2f(-size / 2, size / 2);
            glEnd();
            break;
        case TRIANGLE:
            glBegin(GL_TRIANGLES);
                glVertex2f(-size / 2, -size / 2);
                glVertex2f(size / 2, -size / 2);
                glVertex2f(0, size / 2);
            glEnd();
            break;
        case CIRCLE:
            glBegin(GL_POLYGON);
            for(int i = 0; i < 360; i++){
                float degInRad = i * 3.14159 / 180;
                glVertex2f(cos(degInRad) * size / 2, sin(degInRad) * size / 2);
            }
            glEnd();
            break;
    }

    glPopMatrix();
}

void NPC::shootBullets() {
    const float BULLET_SPEED = 3.5f;  // Define speed of bullets

    // Check if enough time has passed since the last shot
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastShotTime >= shootingInterval) {
        lastShotTime = currentTime;

        // Create and store 4 bullets
        bullets.push_back(Bullet(posX, posY + BULLET_SPEED, BULLET_SPEED, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f )); // Up
        bullets.push_back(Bullet(posX - BULLET_SPEED, posY, BULLET_SPEED, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f)); // Left
        bullets.push_back(Bullet(posX + BULLET_SPEED, posY, BULLET_SPEED, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f)); // Right
        bullets.push_back(Bullet(posX, posY - BULLET_SPEED, BULLET_SPEED, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f)); // Down
    }
}

void NPC::markForRemoval(){
    markedForRemoval = true;
}

void NPC::removeMarkedBullets() {
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
        return bullet.getMarkedForRemoval();
    }), bullets.end());
}

bool NPC::getMarkedForRemoval() const {
    return markedForRemoval;
}

std::vector<Bullet>& NPC::getBullets(){
    return bullets;
}

bool NPC::checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const{
    return (std::abs(bulletX - posX) < (size / 2 + bulletSize / 2)) &&
           (std::abs(bulletY - posY) < (size / 2 + bulletSize / 2));
}

bool NPC::checkCollisionWithPlayer(float playerX, float playerY, float playerSize) const {
    return (std::abs(playerX - posX) < (size / 2 + playerSize / 2)) &&
           (std::abs(playerY - posY) < (size / 2 + playerSize / 2));
}