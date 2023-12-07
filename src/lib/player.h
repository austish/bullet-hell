// Player class
#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
        bool keyStates[256];
        float posX;
        float posY;
        float size = 40.0f;
        float speed = 5.0f;
        int score;
        int health;
    public:
        Player();
        // Player movement
        void updatePlayer();
        // Update movement keystates
        void updateKey(unsigned char key, bool value);
        void updateHealth(int amount);
        void updateScore(int amount);
        int getScore();
        int getHealth();
        void resetPlayer();
        void drawPlayer();
};


#endif