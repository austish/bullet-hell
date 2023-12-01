// Player class
#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
        bool keyStates[256];
        float playerPosX;
        float playerPosY;
        float playerSize = 40.0f;
        float playerSpeed = 5.0f;
    public:
        Player();
        void updatePlayer();
        float getPosX();
        float getPosY();
        float getSize();
        void updateKey(unsigned char key, bool value);
};

#endif