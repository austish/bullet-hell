#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include <vector>

class Player {
    private:
        bool keyStates[256];
<<<<<<< Updated upstream
        float playerPosX;
        float playerPosY;
        float playerSize = 40.0f;
        float playerSpeed = 5.0f;
=======
        float posX;
        float posY;
        float size = 40.0f;
        float speed = 5.0f;
        std::vector<Bullet> bullets;
        float bulletSpeed;
>>>>>>> Stashed changes
    public:
        Player();
        void updatePlayer();
        float getPosX();
        float getPosY();
        float getSize();
        void updateKey(unsigned char key, bool value);
<<<<<<< Updated upstream
=======
        void drawPlayer();
        void shootBullet(float mouseX, float mouseY);
        std::vector<Bullet>& getBullets();
        void removeMarkedBullets();
        float getPosX();
        float getPosY();
>>>>>>> Stashed changes
};

#endif