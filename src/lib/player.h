#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include <vector>

class Player {
    private:
        bool keyStates[256];
        float posX;
        float posY;
        float size = 40.0f;
        float speed = 5.0f;
        std::vector<Bullet> bullets;
    public:
        Player();
        // Player movement
        void updatePlayer();
        // Update movement keystates
        void updateKey(unsigned char key, bool value);
        void drawPlayer();
        void shootBullet(int mouseX, int mouseY);
        std::vector<Bullet>& getBullets();
        void removeMarkedBullets();
        float getPosX();
        float getPosY();
        bool checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const;
};


#endif