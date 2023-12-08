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
        int score;
        int health;
    public:
        Player();
        void updatePlayer();
        void drawPlayer();
        // Update movement keystates
        void updateKey(unsigned char key, bool value);
        void shootBullet(int mouseX, int mouseY);
        void removeMarkedBullets();
        void updateHealth(int amount);
        void updateScore(int amount);
        std::vector<Bullet>& getBullets();
        float getPosX();
        float getPosY();
        int getScore();
        int getHealth();
        float getSize() const;
        void resetPlayer();
        bool checkCollisionWithBullet(float bulletX, float bulletY, float bulletSize) const;
};


#endif
